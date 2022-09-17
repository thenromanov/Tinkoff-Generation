}
        int i = 1;
        while (block[i] == sqroot) i++;
        i *= sqroot;
        while (count[i] > 0) i++;
        return i;