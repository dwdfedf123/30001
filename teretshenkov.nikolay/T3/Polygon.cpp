#include "Polygon.h"

std::istream& operator>>(std::istream& in, DelimiterIO&& dest)
{
    std::istream::sentry sentry(in);
    if (!sentry)
    {
        return in;
    }
    char symb = '0';
    in >> symb;
    if (in && (std::tolower(symb) != std::tolower(dest.exp)))
    {
        in.setstate(std::ios::failbit);
    }
    return in;
}


std::istream& operator>>(std::istream& in, intIO&& dest)
{
    std::istream::sentry sentry(in);
    if (!sentry)
    {
        return in;
    }

    in >> dest.ref;
    if (!in)
    {
        in.setstate(std::ios::failbit);
    }
    return in;
}



//������ �����      3 (1;1) (1;3) (3;3)
std::istream& operator>>(std::istream& in, Polygon& dest)
{
    std::istream::sentry sentry(in);
    if (!sentry)
    {
        return in;
    }
    Iofmtguard fmtguard(in);

    Polygon polygon;

    int nPoints = 0;
    in >> nPoints;
    int temp = 0;
    for (int i = 0; i < nPoints; ++i)
    {
        Point point;
        in >> DelimiterIO{ '(' };
        in >> intIO{ temp };
        point.x = temp;
        in >> DelimiterIO{ ';' };
        in >> intIO{ temp };
        point.y = temp;
        in >> DelimiterIO{ ')' };
        if (in)
        {
            polygon.points.push_back(point);
        }
    }

    if (in)
    {
        dest = polygon;
    }
    return in;
}
