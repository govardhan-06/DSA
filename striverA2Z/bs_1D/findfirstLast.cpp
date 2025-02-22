class Solution
{
public:
    vector<int> searchRange(vector<int> &v, int key)
    {
        int first = -1, last = -1;
        int start = 0, end = v.size() - 1;

        while (start <= end)
        {
            int mid = start + (end - start) / 2;
            if (v[mid] == key)
            {
                first = mid;
                end = mid - 1;
            }
            else if (key < v[mid])
            {
                end = mid - 1;
            }
            else
            {
                start = mid + 1;
            }
        }

        start = 0, end = v.size() - 1;

        while (start <= end)
        {
            int mid = start + (end - start) / 2;
            if (v[mid] == key)
            {
                last = mid;
                start = mid + 1;
            }
            else if (key < v[mid])
            {
                end = mid - 1;
            }
            else
            {
                start = mid + 1;
            }
        }
        return {first, last};
    }
};