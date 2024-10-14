union V2i
{
    struct
    {
        int32 X;
        int32 Y;
    };
    struct
    {
        int32 Width;
        int32 Height;
    };
    struct
    {
        int32 Min;
        int32 Max;
    };
    int32 Values[2];
};

union V2r
{
    struct
    {
        real32 X;
        real32 Y;
    };
    struct
    {
        real32 Width;
        real32 Height;
    };
    struct
    {
        real32 Min;
        real32 Max;
    };
    real32 Values[2];
};

union V2u
{
    struct
    {
        uint32 X;
        uint32 Y;
    };
    struct
    {
        uint32 Width;
        uint32 Height;
    };
    struct
    {
        uint32 Min;
        uint32 Max;
    };
    uint32 Values[2];
};

int32 DotProduct(V2i a, V2i b);

V2i operator+(V2i a, V2i b);
V2i &operator+=(V2i &a, V2i b);
V2i operator-(V2i a, V2i b);
V2i &operator-=(V2i &a, V2i b);
V2i operator*(V2i a, int32 b);
V2i &operator*=(V2i &a, int32 b);
V2i operator*(int32 a, V2i b);
V2i operator*(V2i a, real32 b);
V2i &operator*=(V2i &a, real32 b);
V2i operator*(real32 a, V2i b);
bool32 operator!=(V2i a, V2i b);
bool32 operator==(V2i a, V2i b);

void Normalize(V2r& vector);
real32 DotProduct(V2r a, V2r b);

V2r operator+(V2r a, V2r b);
V2r &operator+=(V2r& a, V2r b);
V2r operator-(V2r a, V2r b);
V2r &operator-=(V2r& a, V2r b);
V2r operator*(V2r a, real32 b);
V2r &operator*=(V2r &a, real32 b);
V2r operator*(real32 a, V2r b);
V2r operator*(V2r a, int32 b);
V2r &operator*=(V2r &a, int32 b);
V2r operator*(int32 a, V2r b);
bool32 operator!=(V2r a, V2r b);
bool32 operator==(V2r a, V2r b);

uint32 DotProduct(V2u a, V2u b);

V2u operator+(V2u a, V2u b);
V2u &operator+=(V2u &a, V2u b);
V2u operator-(V2u a, V2u b);
V2u &operator-=(V2u &a, V2u b);
V2u operator*(V2u a, uint32 b);
V2u &operator*=(V2u &a, uint32 b);
V2u operator*(uint32 a, V2u b);
V2u operator*(V2u a, real32 b);
V2u &operator*=(V2u &a, real32 b);
V2u operator*(real32 a, V2u b);
bool32 operator!=(V2u a, V2u b);
bool32 operator==(V2u a, V2u b);
