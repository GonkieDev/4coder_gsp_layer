internal u64
BitOffset(u64 value)
{
    u64 offset = 0;
    for(u64 i = 0; i < 64; i += 1)
    {
        if(value == ((u64)1 << i))
        {
            offset = i;
            break;
        }
    }
    return offset;
}

function f32
MinimumF32(f32 a, f32 b)
{
    return a < b ? a : b;
}

function f32
MaximumF32(f32 a, f32 b)
{
    return a > b ? a : b;
}
