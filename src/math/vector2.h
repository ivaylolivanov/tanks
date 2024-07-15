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
    real32 Values[2];
};

void Normalize(V2i& vector);
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
bool operator!=(V2i a, V2i b);

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
bool operator!=(V2r a, V2r b);
