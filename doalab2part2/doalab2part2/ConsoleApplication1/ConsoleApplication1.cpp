#include<iostream>
#include<algorithm>
#include<vector>

void swap(std::vector<int>& arr, int a, int b) {
    int temp = arr[a];
    arr[a] = arr[b];
    arr[b] = temp;
}

// searches for pivot and partitions the vector around it
int partition(std::vector<int>& arr, int f, int b, int pivot) {
    // searches for the pivot and moves it to the end of the vector
    int i;
    for (i = f; i < b; i++) {
        if (arr[i] == pivot) {
            break;
        }
    }
    swap(arr, i, b);

    i = f;
    for (int j = f; j <= b - 1; j++) {
        if (arr[j] <= pivot) {
            swap(arr, i, j);
            i++;
        }
    }
    swap(arr, i, b);
    return i;
}

int findMedian(std::vector<int>& arr) {
    sort(arr.begin(), arr.end());
    for (int i = 0; i < arr.size(); i++) {
        std::cout << i << ": " << arr[i] << "\n";
    }
    std::cout << "______________________________" << "\n";
    return arr[arr.size() / 2];  // return middle element
}

// returns kth smallest element
int kthSmallest(std::vector<int> &arr, int f, int b, int k) {
    // if k is smaller than size of vector
    if (k > 0 && k <= arr.size()) {
        int n = arr.size();

        int i;
        int place = 0;
        std::vector<int> median;

        // divide arr in groups of size 5, calculate median
        // of every group and store it in median vector
        for (i = 0; i < n / 5; i++) {
            std::vector<int> temp(arr.begin() + place, arr.begin() + (i + 1) * 5);
            median.push_back(findMedian(temp));
            place += 5;
        }
        if (i * 5 < n) { // find the median of the remaining elements
            std::vector<int> temp(arr.begin() + place, arr.end());
            median.push_back(findMedian(temp));
            i++;
        }

        // find median of all medians.
        int medOfMed = (i == 1) ? median[i - 1] :
            kthSmallest(median, 0, i - 1, i / 2);

        // partition the array around median of medians and
        // get the final position of pivot in sorted vector
        int pos = partition(arr, f, b, medOfMed);

        // if position index is same as k
        if (pos - f == k - 1)
            return arr[pos];
        if (pos - f > k - 1)  // if position is more, check left side
            return kthSmallest(arr, f, pos - 1, k);

        // otherwise check right side
        return kthSmallest(arr, pos + 1, b, k - pos + f - 1);
    }

    if (k > arr.size() || k <= 0) {
        std::cout << "Nice try but you're going to get a -1 instead idiot" << "\n";
        return -1;
    }    
}



int main() {
    std::vector<int> arr = { 12, 3, 5, 200, 4, 19, 26, 7, 8, 11, 7 };
    int n = arr.size(), k = 2;
    std::cout << "K'th smallest element is "
        << kthSmallest(arr, 0, n - 1, k);
    return 0;
}