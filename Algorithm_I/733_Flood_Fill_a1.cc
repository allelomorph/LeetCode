#include <iostream>
#include <vector>


template<typename T>
const std::string PrintableNestedVector(
    const std::vector<std::vector<T>> &nv) {
    std::string result;
    result.push_back('[');
    for (const auto &v: nv) {
        result.push_back('[');
        for (const auto &o: v) {
            result.append(std::to_string(o) + ",");
        }
            if (result.back() == ',')
                result.back() = ']';
            else
                result.push_back(']');
    }
    if (result.back() == ',')
        result.back() = ']';
    else
        result.push_back(']');
    return result;
}


// Time to complete: 25 mins

// Needed to research:

//// Begin solution, results at https://leetcode.com/submissions/detail/741313019/


class Solution {
public:
    // m == image.length
    // n == image[i].length
    // 1 <= m, n <= 50
    // 0 <= image[i][j], color < 216
    // 0 <= sr < m
    // 0 <= sc < n
    // recursive function that paints the pixel if it's the correct color,
    //   then recurses on neighboring pixels.
    /**
     * An image is represented by an m by n integer grid, where
     * image[i][j] represents the pixel value of the image.
     *
     * Given three integers sr, sc, and color; performs a flood fill on
     * the image starting from the pixel image[sr][sc].
     *
     * Performing a flood fill begins with the starting pixel, and spreads
     * to a region of contiguous pizels of the same color (each pixel in
     * fill region shares at least one side with another in the region.)
     *
     * Returns the modified image after performing the flood fill.
     */
    std::vector<std::vector<int>> &floodFill(
        std::vector<std::vector<int>> &image,
        const int sr, const int sc, const int color) {
        if (image[sr][sc] != color) {
            floodFillRecurse(image, sr, sc,
                             int(image.size()), int(image[0].size()),
                             image[sr][sc], color);
        }
        return image;
    }
private:
    // Is there an advantage in making y_sz, x_sz, old_color, and fill_color
    //   instance variables instead of passing them through each recursion
    //   frame? Or will the compiler optimize them if marked const?
    void floodFillRecurse(std::vector<std::vector<int>> &image,
                          const int y, const int x,
                          const int y_sz, const int x_sz,
                          const int old_color, const int fill_color) {
        if (y < 0 || x < 0 || y >= y_sz || x >= x_sz)
            return;   // out of bounds
        if (image[y][x] != old_color)
            return;   // out of fill region
        image[y][x] = fill_color;
        floodFillRecurse(image, y - 1, x, y_sz, x_sz,
                         old_color, fill_color);  // up
        floodFillRecurse(image, y + 1, x, y_sz, x_sz,
                         old_color, fill_color);  // down
        floodFillRecurse(image, y, x - 1, y_sz, x_sz,
                         old_color, fill_color);  // left
        floodFillRecurse(image, y, x + 1, y_sz, x_sz,
                         old_color, fill_color);  // right
    }
};


//// end solution


int main() {
    std::vector<std::vector<int>> image1 {
        {1,1,1},
        {1,1,0},
        {1,0,1}
    };
    const int sr1 {1};
    const int sc1 {1};
    const int color1 {2};
    std::vector<std::vector<int>> image2 {
        {0,0,0},
        {0,0,0}
    };
    const int sr2 {0};
    const int sc2 {0};
    const int color2 {0};

    Solution solution;

    std::cout << "solution.floodFill(" << PrintableNestedVector(image1) <<
        ", " << sr1 << ", " << sc1 << ", " << color1 << "): " <<
        PrintableNestedVector(solution.floodFill(image1, sr1, sc1, color1)) <<
        '\n';
    // [[2,2,2],[2,2,0],[2,0,1]]
    // Note the bottom corner is not colored 2, because it is not
    //   4-directionally connected to the starting pixel.

    std::cout << "solution.floodFill(" << PrintableNestedVector(image2) <<
        ", " << sr2 << ", " << sc2 << ", " << color2 << "): " <<
        PrintableNestedVector(solution.floodFill(image2, sr2, sc2, color2)) <<
        '\n';
    // [[0,0,0],[0,0,0]]
    // The starting pixel is already colored 0, so no changes are made to the
    //   image.
}
