union V3r
{
    struct
    {
        real32 X;
        real32 Y;
        real32 Z;
    };
    struct
    {
        real32 R;
        real32 G;
        real32 B;
    };
    real32 Values[3];
};

V3r operator+(V3r a, V3r b);
V3r &operator+=(V3r &a, V3r b);
V3r operator-(V3r a, V3r b);
V3r &operator-=(V3r &a, V3r b);
V3r operator*(V3r a, int32 b);
V3r operator*(int32 a, V3r b);
V3r operator*(V3r a, real32 b);
V3r operator*(real32 a, V3r b);
V3r &operator*=(V3r &a, real32 b);
V3r &operator*=(V3r &a, int32 b);
