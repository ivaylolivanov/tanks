#include <X11/X.h>
#include <X11/Xutil.h>
#include <X11/Xlib.h>
#include <cstddef>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

#include "../../tanks.h"
#include "linux.h"

GlobalVariable bool32 IS_RUNNING = false;
GlobalVariable BackBuffer BACK_BUFFER;

// TODO: Make the signature same as in Windows. This is important
void FreeFileMemory(ThreadContext* thread, void* memory, int length = 0)
{
    if (!memory) return;

    munmap(memory, length);
}

ReadFileResult ReadFile(ThreadContext* thread, char* filename)
{
    ReadFileResult result = {};
    result.Size = 0;
    result.Content = 0;

    int32 file_descriptor = open(filename, O_RDONLY);
    if (file_descriptor < 0)
        return result;

    struct stat file_stat = {};
    if (fstat(file_descriptor, &file_stat) < 0)
        return result;

    result.Size = file_stat.st_size;
    result.Content = mmap(0, result.Size, PROT_READ | PROT_WRITE,
        MAP_PRIVATE | MAP_ANONYMOUS, file_descriptor, 0);
    if (result.Content == MAP_FAILED)
        return result;

    close(file_descriptor);
    return result;
}

bool32 WriteFile(ThreadContext* thread, char* filename, uint32 size,
    void *memory)
{
    bool32 result = false;

    int32 file_descriptor = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (file_descriptor < 0)
        return result;

    int32 bytes_written = write(file_descriptor, memory, size);
    result = ((uint32)bytes_written == size);

    close(file_descriptor);

    return result;
}

// Internal int GetExeFilepath(char* filepath, int size);

Internal void ResizeBuffer(BackBuffer *buffer, int width, int height)
{
    if (buffer->Memory)
        munmap(buffer->Memory, buffer->Pitch * buffer->Height);

    int bytes_per_pixel = 4;

    buffer->Width = width;
    buffer->Height = height;
    buffer->BytesPerPixel = bytes_per_pixel;
    buffer->Pitch = width * buffer->BytesPerPixel;

    uint32 size = buffer->Pitch * buffer->Height;
    buffer->Memory = mmap(0, size, PROT_READ | PROT_WRITE,
        MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

    if (buffer->Memory == MAP_FAILED)
    {
        buffer->Width = 0;
        buffer->Height = 0;
    }
}

Internal void InitializeWindow(Display* display, Window* window, int screen)
{
    int32 window_event_mask = ExposureMask | KeyPressMask | StructureNotifyMask
        | KeyReleaseMask | PointerMotionMask | ButtonPressMask
        | ButtonReleaseMask;

    // Set up window attributes
    XSetWindowAttributes attributes;
    attributes.background_pixel = BlackPixel(display, screen);
    attributes.border_pixel = WhitePixel(display, screen);
    attributes.event_mask = window_event_mask;

    Window root_window = RootWindow(display, screen);
    *window = XCreateWindow(
        display, root_window,
        SCREEN_ORIGIN_X, SCREEN_ORIGIN_Y,
        SCREEN_WIDTH, SCREEN_HEIGHT,
        SCREEN_BORDER_WIDTH,
        CopyFromParent,
        InputOutput,
        CopyFromParent,
        CWBackPixel | CWBorderPixel | CWEventMask,
        &attributes);

    XSelectInput(display, *window, window_event_mask);
    XMapWindow(display, *window);
}

Internal bool InitializePlatformAndMemory(LinuxState* linux_state,
    GameMemory* game_memory)
{
    bool result = false;

    int32 symbols_read = readlink("/proc/self/exe", linux_state->ExeFilepath,
        sizeof(linux_state->ExeFilepath));

    game_memory->PermanentStorageSize = MEGABYTES(64);
    game_memory->TransientStorageSize = GIGABYTES(1);
    // TODO: Make the signature same as in Windows. This is important.
    // game_memory.FreeFileMemory = FreeFileMemory;
    game_memory->ReadFile = ReadFile;
    game_memory->WriteFile = WriteFile;

    linux_state->TotalSize = game_memory->PermanentStorageSize
        + game_memory->TransientStorageSize;
    linux_state->GameMemory = mmap(0, linux_state->TotalSize,
        PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

    game_memory->PermanentStorage = linux_state->GameMemory;
    game_memory->TransientStorage = ((uint8 *)game_memory->PermanentStorage
        + game_memory->PermanentStorageSize);

    result = game_memory->PermanentStorage && game_memory->TransientStorage;

    return result;
}

Internal void ProcessKeyboardButton(ButtonState *state, bool32 is_down)
{
    if (state->EndedDown != is_down)
    {
        state->EndedDown = is_down;
        ++state->HalfTransitions;
    }
}

Internal XFontStruct* InitializeFont(Display* display, GC graphic_context)
{
    XFontStruct* font = XLoadQueryFont(display, FONT_NAME);
    if (!font)
    {
        fprintf(stderr, "\nFailed to load font\n\n");
        font = 0;
    }

    XSetFont(display, graphic_context, font->fid);
    return font;
}

Internal void DisplayText(char* text, int x, int y, XFontStruct* font,
    Display* display, Window* window, GC graphic_context)
{
    uint8 length = strlen(text);
    uint8 width = XTextWidth(font, text, length);

    XDrawString(display, *window, graphic_context, x, y, text, length);
}

int main()
{
    Display *display = XOpenDisplay(0);
    if (display == 0)
    {
        fprintf(stderr, "Cannot open display\n");
        return 1;
    }

    LinuxState linux_state = {};
    GameMemory game_memory = {};
    if (!InitializePlatformAndMemory(&linux_state, &game_memory))
        return 0;

    int screen = DefaultScreen(display);
    int default_depth = DefaultDepth(display, screen);
    Visual* visual = DefaultVisual(display, screen);

    Window window;
    InitializeWindow(display, &window, screen);

    GC graphic_context = XCreateGC(display, window, 0, 0);

    XFontStruct* font = InitializeFont(display, graphic_context);

    IS_RUNNING = true;
    ResizeBuffer(&BACK_BUFFER, SCREEN_WIDTH, SCREEN_HEIGHT);
    XImage* image = XCreateImage(display, visual, default_depth, ZPixmap, 0,
        (char*)BACK_BUFFER.Memory, BACK_BUFFER.Width, BACK_BUFFER.Height, 32, 0);
    if (!image)
    {
        fprintf(stderr, "Unable to create a XImage!");
        IS_RUNNING = false;
    }

    XEvent event;
    while (IS_RUNNING)
    {
        XNextEvent(display, &event);
        if (event.type == Expose)
        {
            uint8* row = ((uint8 *)BACK_BUFFER.Memory);
            for (int y = 0; y < BACK_BUFFER.Height; ++y)
            {
                uint32* pixel = (uint32*)row;
                for (int x = 0; x < BACK_BUFFER.Width; ++x)
                {
                    *pixel++ = 0xff1224;
                }

                row += BACK_BUFFER.Pitch;
            }
            // image->data = (char*)BACK_BUFFER.Memory;

            XPutImage(display, window, DefaultGC(display, screen), image, 0, 0,
                0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

            int display_text_x = 100;
            int display_text_y = 100;
            DisplayText("This is a test string", display_text_x, display_text_y,
                font, display, &window, graphic_context);
        }

        if (event.type == KeyPress)
        {
            KeySym key;
            char buffer[1];
            XLookupString(&event.xkey, buffer, 1, &key, NULL);

            if (key == XK_Escape)
                IS_RUNNING = false;
        }
    }


    munmap(BACK_BUFFER.Memory, BACK_BUFFER.Pitch * BACK_BUFFER.Height);
    munmap(linux_state.GameMemory, linux_state.TotalSize);
    XDestroyWindow(display, window);
    XCloseDisplay(display);

    return 0;
}
