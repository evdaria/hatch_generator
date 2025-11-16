#include "hatch_generator.h"

#include <iostream>
#include <math.h>
#include <algorithm>
#include <fstream>

const double EPSILON = 1e-6; // Погрешность для сравнений с плавающей точкой

Point_2 HatchGenerator::rotatePoint(const Point_2 &point, double angle) const
{
    // Преобразование угла в радианы
    double rad = angle * M_PI / 180.0;

    double cosRad = cos(rad);
    double sinRad = sin(rad);

    double x = point.x * cosRad - point.y * sinRad;
    double y = point.x * sinRad + point.y * cosRad;

    if (std::abs(x) < EPSILON) x = 0.0;
    if (std::abs(y) < EPSILON) y = 0.0;

    return Point_2(x, y);
}

HatchGenerator::HatchGenerator(const std::vector<Point_2> &contour, double angle, double step) : contour_(contour), angle_(angle), step_(step) {}


std::vector<Line_2> HatchGenerator::generateHatchLines() const
{
    std::vector<Line_2> res;
    if (contour_.empty()) return res;

    std::vector<Point_2> rotateContour;
    for (const auto& p : contour_) {
        rotateContour.push_back(rotatePoint(p, -angle_));
    }

    double minX = 0.0;
    double minY = 0.0;
    double maxX = 0.0;
    double maxY = 0.0;
    findBounds(rotateContour, minX, minY, maxX, maxY);

    for (int i = 0; ; ++i) {
        double y = minY + i * step_;
        if (y > maxY + EPSILON) break;

        std::vector<double> intersections = findHorizontalIntesections(rotateContour, y);

        if (intersections.size() == 2) {
            Point_2 p1Rotated(intersections[0], y);
            Point_2 p2Rotated(intersections[1], y);

            Line_2 line(rotatePoint(p1Rotated, angle_), rotatePoint(p2Rotated, angle_));
            res.push_back(line);
        }
    }

    return res;
}

void HatchGenerator::printHatchLines(const std::vector<Line_2> &lines) const
{
    for (size_t i = 0; i < lines.size(); ++i) {
        printf("Line %zu: (%.3f,%.3f) -> (%.3f,%.3f)\n",
               i + 1, lines[i].start.x, lines[i].start.y, lines[i].end.x, lines[i].end.y);
    }
}

void HatchGenerator::saveToSVG(const std::vector<Line_2> &lines, const std::string &filename) const
{
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    double minX, minY, maxX, maxY;
    findBounds(contour_, minX, minY, maxX, maxY);

    double padding = 10.0;
    double scale = 10.0;
    double width = ((maxX - minX) + 2 * padding) * scale;
    double height = ((maxY - minY) + 2 * padding) * scale;

    // Заголовок SVG
    file << "<svg width=\"" << width << "\" height=\"" << height << "\" xmlns=\"http://www.w3.org/2000/svg\">\n";

    // Фон
    file << "  <rect width=\"100%\" height=\"100%\" fill=\"white\"/>\n";

    // Смещение всех координат и масштабирование
    file << "  <g transform=\"translate(" << (padding - minX) * scale << " " << (padding - minY) * scale << ") scale(" << scale << ")\">\n";

    // Контур прямоугольника
    file << "    <polygon points=\"";
    for (const auto& p : contour_) {
        file << p.x << "," << p.y << " ";
    }
    file << "\" fill=\"none\" stroke=\"black\" stroke-width=\"0.1\"/>\n";

    // Штриховка
    for (size_t i = 0; i < lines.size(); ++i) {
        const auto& line = lines[i];
        file << "    <line x1=\"" << line.start.x << "\" y1=\"" << line.start.y
             << "\" x2=\"" << line.end.x << "\" y2=\"" << line.end.y
             << "\" stroke=\"red\" stroke-width=\"0.1\"/>\n";
    }

    file << "  </g>\n";
    file << "</svg>\n";
    file.close();

    std::cout << "SVG saved to: " << filename << std::endl;
}

void HatchGenerator::findBounds(const std::vector<Point_2> &contour, double &minX, double &minY, double &maxX, double &maxY) const
{
    if (contour.empty()) return;

    minX = maxX = contour[0].x;
    minY = maxY = contour[0].y;

    for (const auto& p : contour) {
        minX = std::min(minX, p.x);
        maxX = std::max(maxX, p.x);
        minY = std::min(minY, p.y);
        maxY = std::max(maxY, p.y);
    }
}

std::vector<double> HatchGenerator::findHorizontalIntesections(const std::vector<Point_2> &contour, double yLine) const
{
    std::vector<double> intersections;

    int n = contour.size();

    if (n != 4) {
        std::cerr << "Error: contur must have exactly 4 points for rectangle, got " << contour.size() << std::endl;
        return intersections;
    }

    for(int i = 0; i < n; ++i) {
        Point_2 p1 = contour[i];
        Point_2 p2 = contour[(i + 1) % n];

        if ((p1.y < yLine && yLine < p2.y) || (p2.y < yLine && yLine < p1.y)) {
            if (std::abs(p1.y - p2.y) > EPSILON) {
                double t = (yLine - p1.y) / (p2.y - p1.y);
                double intersectX = p1.x + t * (p2.x - p1.x);
                intersections.push_back(intersectX);
            }
        }
    }

    if (intersections.size() % 2 != 0) {
        intersections.clear();
    }

    std::sort(intersections.begin(), intersections.end());

    return intersections;
}


