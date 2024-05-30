#include "Polygon.h"

namespace nspace
{
    bool operator==(const Polygon& first, const Polygon& second)
    {
        if (first.points.size() != second.points.size())
        {
            return false;
        }
        else
        {
            /*bool result = true;
            for (long unsigned int i = 0; i < this->points.size(); i++)
            {
                if (this->points[i].x != other.points[i].x || this->points[i].y != other.points[i].y)
                {
                    result = false;
                }
            }
            return result;*/
            return std::equal(first.points.cbegin(), first.points.cend(), second.points.cbegin());
        }
    }

    std::istream& operator>>(std::istream& in, DelimiterIO&& dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
        char c = '0';
        in >> c;
        if (in && (std::tolower(c) != std::tolower(dest.exp)))
        {
            in.setstate(std::ios::failbit);
        }
        return in;
    }

    std::istream& operator>>(std::istream& in, IntIO&& dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }

        int base = 0;
        in >> base;
        dest.ref = base;
        if (!in)
        {
            in.setstate(std::ios::failbit);
        }
        return in;
    }

    std::istream& operator>>(std::istream& in, Polygon& dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }

        long unsigned int countOfPoints = 0;
        in >> countOfPoints;
        if (countOfPoints < 3)
        {
            in.setstate(std::ios::failbit);
            return in;
        }
        else
        {
            Polygon figure;
            using skip = DelimiterIO;
            using count = IntIO;

            for (long unsigned int i = 0; i < countOfPoints; i++)
            {
                Point point;
                in >> skip{ '(' };
                in >> count{ point.x };
                in >> skip{ ';' };
                in >> count{ point.y };
                in >> skip{ ')' };

                figure.points.push_back(point);
            }
            if (figure.points.size() != countOfPoints)
            {
                in.setstate(std::ios::failbit);
            }
            dest = figure;
            return in;
        }
    }

    iofmtguard::iofmtguard(std::basic_ios< char >& s) :
        s_(s),
        fill_(s.fill()),
        precision_(s.precision()),
        fmt_(s.flags())
    {}

    iofmtguard::~iofmtguard()
    {
        s_.fill(fill_);
        s_.precision(precision_);
        s_.flags(fmt_);
    }
}

