bool massort(int* mass, int first_index, int last_index)
{
    int i = first_index,
        j = last_index,
        x = *(mass + first_index), // sapporting element
        temp = 0; // look 1

    bool IO = true;

    if (first_index == last_index) return false;

    do
    {
        if (IO)while ((*(mass + j) >= x) && j > i) j--;
        if (!IO)while ((*(mass + i) < x) && i < j) i++;

        // 1. 
        temp = *(mass + i);
        *(mass + i) = *(mass + j);
        *(mass + j) = temp;
        // .1

        // switch.
        if (IO) IO = false;
        else if (!IO) IO = true;
        // .switch

    } while (i != j);

    if (last_index > i + 1)
        massort(mass, i + 1, last_index);
    if (first_index < j - 1)
        massort(mass, first_index, j - 1);

    return true;
}