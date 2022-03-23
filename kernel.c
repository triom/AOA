
/* original */


void baseline (int n, float a[n], float b[n], float c[n], float d[20]) {
  
    unsigned i, k;

    
    // all elements in b are assumed positive

    for (k = 0; k < 20; k++)
    {
        for (i = 0; i < n; i++)
        {
            if (b[i] >= 0.0 && b[i] < 1.0)
            {
                a[i] += exp(b[i] + d[k]) / c[i];
            }
            else if (b[i] >= 1.0)
            {
                a[i] += (b[i] * d[k]) / c[i];
            }
        }
    }
        
}


