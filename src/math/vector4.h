union V4r
{
    struct
    {
        real32 X;
        real32 Y;
        real32 Z;
        real32 W;
    };
    struct
    {
        real32 Red;
        real32 Green;
        real32 Blue;
        real32 Alpha;
    };
    real32 Values[4];
};

V4r operator+(V4r a, V4r b);
V4r &operator+=(V4r &a, V4r b);
V4r operator-(V4r a, V4r b);
V4r &operator-=(V4r &a, V4r b);
V4r operator*(V4r a, int32 b);
V4r &operator*=(V4r &a, int32 b);
V4r operator*(int32 a, V4r b);
V4r operator*(V4r a, real32 b);
V4r &operator*=(V4r &a, real32 b);
V4r operator*(real32 a, V4r b);
