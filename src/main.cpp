#include <iostream>

#include "Rectangle.hpp"

#include <boost/log/trivial.hpp>

int main()
{
    Rectangle r(5, 10);
    BOOST_LOG_TRIVIAL(info) << r.area();
    return 0;
}