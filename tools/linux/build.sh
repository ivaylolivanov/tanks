#!/bin/bash

COMMON_COMPILER_FLAGS=(
    "-g"
    "-gcodeview"
    "-fno-rtti"
    "-O0"
    "-Werror"
    "-Wall"
    "-Wno-unused-variable"
    "-Wno-microsoft-anon-tag"
    "-Wno-writable-strings"
    "-nodefaultlibs");

COMMON_LINKER_FLAGS=(
    "-lX11"
    "-lc");

GAME_NAME='tanks';

function is-in-git-repo()
{
    local directory="$1"; shift 1;

    cd "$directory" || return 1;
    git rev-parse --is-inside-work-tree >/dev/null 2>&1 || return 2;

    return 0;
}

function build()
{
    local working_dir="$1";     shift 1;
    local target_filepath="$1"; shift 1;

    local clang_executable="$(which -a clang | head -n 1)";
    local verbose='-v';

    (
        cd "$working_dir" || exit 1;

        "$clang_executable"               \
            "${COMMON_COMPILER_FLAGS[@]}" \
            "${COMMON_LINKER_FLAGS[@]}"   \
            "$target_filepath"            \
            -o "$GAME_NAME"               \
            "$verbose" || exit 2;
    ) || return $?;

    return 0;
}

function main()
{
    local current_dir="$(pwd)";

    local git_root='';
    local working_dir='';
    local source_dir='';
    local build_target_filepath='';

    is-in-git-repo "$current_dir" ||
    {
        printf -- "\nERROR: %s %s\n"   \
            'Not in a git repository.' \
            'Cannot determine project root!';
        return 1;
    }

    git_root="$(git rev-parse --show-toplevel)";
    working_dir="${git_root}/build";
    source_dir="${git_root}/src";
    build_target_filepath="${source_dir}/platform-layer/linux/main.cpp";

    rm -rvf "$working_dir";
    mkdir -pv "$working_dir";

    build "$working_dir" "$build_target_filepath" || return 2;

    return 0;
}

main || exit $?;
