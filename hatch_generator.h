#ifndef HATCH_GENERATOR_H
#define HATCH_GENERATOR_H

#include <vector>
#include <string>

/// Точка в двумерном пространстве
struct Point_2 {
    double x; //!< Координата X
    double y; //!< Координата Y

    Point_2(double x = 0, double y = 0) : x(x), y(y) {}
};

/// Отрезок линии между двумя точками
struct Line_2 {
    Point_2 start; //!< Начальная точка
    Point_2 end;   //!< Конечная точка

    Line_2(const Point_2& start, const Point_2& end) : start(start), end(end) {}
};

/// Генератор штриховки внутри прямоугольника
class HatchGenerator
{
private:
    std::vector<Point_2> contour_; //!< Контур детали
    double angle_;                 //!< Угол штриховки
    double step_;                  //!< Шаг между линиями штриховки

    /// Поворачивает точку на заданный угол вокруг начала координат
    Point_2 rotatePoint(const Point_2& point, double angle) const;

    /// Находит границы контура по осям X и Y
    void findBounds(const std::vector<Point_2>& contur, double& minX, double& minY, double& maxX, double& maxY) const;

    /// Находит пересечения контура с горизонтальной линией
    std::vector<double> findHorizontalIntesections(const std::vector<Point_2>& contour, double yLine) const;


public:
    HatchGenerator(const std::vector<Point_2>& contour, double angle, double step);

    /// Генерирует линии штриховки
    std::vector<Line_2> generateHatchLines() const;

    /// Выводит линии штриховки в текстовом формате
    void printHatchLines(const std::vector<Line_2>& lines) const;

    /// Сохраняет линии штриховки в SVG файле
    void saveToSVG(const std::vector<Line_2>& lines, const std::string& filename) const;
};

#endif // HATCH_GENERATOR_H
