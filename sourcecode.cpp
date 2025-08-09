#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <utility>

// Function to calculate the determinant of a 3x3 matrix
long long determinant(long long a1, long long a2, long long a3,
                      long long b1, long long b2, long long b3,
                      long long c1, long long c2, long long c3) {
    return a1 * (b2 * c3 - b3 * c2)
         - a2 * (b1 * c3 - b3 * c1)
         + a3 * (b1 * c2 - b2 * c1);
}

int main() {
    // Open the CSV file
    std::ifstream file("coordinates.csv");
    if (!file.is_open()) {
        std::cerr << "Error: Could not open input.csv file. Make sure it exists." << std::endl;
        return 1;
    }

    std::vector<std::pair<long long, long long>> points;
    std::string line;

    // Read the file line by line
    while (std::getline(file, line)) {
        size_t commaPos = line.find(',');
        if (commaPos == std::string::npos) {
            std::cerr << "Warning: Skipping malformed line in CSV." << std::endl;
            continue;
        }

        try {
            long long x = std::stoll(line.substr(0, commaPos));
            long long y = std::stoll(line.substr(commaPos + 1));
            points.push_back({x, y});
        } catch (const std::exception& e) {
            std::cerr << "Error: Could not parse a line from the CSV file." << std::endl;
            return 1;
        }
    }

    file.close();

    if (points.size() < 3) {
        std::cerr << "Not enough points to solve the quadratic equation. Need at least 3 points." << std::endl;
        return 1;
    }

    // Use the first three points for the calculation
    long long x1 = points[0].first, y1 = points[0].second;
    long long x2 = points[1].first, y2 = points[1].second;
    long long x3 = points[2].first, y3 = points[2].second;

    // Set up the determinants for Cramer's Rule
    long long D = determinant(x1*x1, x1, 1,
                              x2*x2, x2, 1,
                              x3*x3, x3, 1);

    long long Da = determinant(y1, x1, 1,
                               y2, x2, 1,
                               y3, x3, 1);

    long long Db = determinant(x1*x1, y1, 1,
                               x2*x2, y2, 1,
                               x3*x3, y3, 1);

    long long Dc = determinant(x1*x1, x1, y1,
                               x2*x2, x2, y2,
                               x3*x3, x3, y3);

    if (D == 0) {
        std::cerr << "Error: The determinant D is zero. The points may be collinear, or the calculation failed." << std::endl;
        return 1;
    }

    // Calculate coefficients a, b, and c
    long long a = Da / D;
    long long b = Db / D;
    long long c = Dc / D;

    // Print the results
    std::cout << "Decoded Points:\n";
    for (const auto& p : points) {
        std::cout << "(" << p.first << ", " << p.second << ")\n";
    }

    std::cout << "\nPolynomial: F(x) = " << a << "x^2 + " << b << "x + " << c << std::endl;
    std::cout << "Secret (c) = " << c << std::endl;

    return 0;
}