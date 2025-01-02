## Pascal's triangle

### Three variations of questions:

1. Variation 1: Finding out an element in position (r,c) from the triangle
   Best way is to find it directly without generating the pascal's triangle
   Formula: `(r-1)C(c-1)`
   [`nCr = n! / (r! * (n-r)!)`]

   Algo:

   ```bash
   We can optimize this calculation by the following observation.
   Assume, given r = 7, c = 4.
   Now, n = r-1 = 7-1 = 6 and r = c-1 = 4-1 = 3
   Let’s calculate 6C3 = 6! / (3! *(6-3)!) = (6*5*4*3*2*1) / ((3*2*1)*(3*2*1))
   This will boil down to (6*5*4) / (3*2*1)
   So, nCr = (n*(n-1)*(n-2)*.....*(n-r+1)) / (r*(r-1)*(r-2)*....1)

   Now, we will use this optimized formula to calculate the value of nCr. But while implementing this into code we will take the denominator in the forward direction like:

   (n / 1)*((n-1) / 2)*.....*((n-r+1) / r).
   ```
