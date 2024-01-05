#include <SFML/Graphics.hpp>
#include <iostream>
#include <map>
#include <iterator>
#include <ctime>
#include "Vec2.h"

struct Intersection { bool result; Vec2 position; };
struct LineSegment { Vec2 start, end; };

Intersection checkIntersection(Vec2 a, Vec2 b, Vec2 c, Vec2 d)
{
    Vec2 r = b - a;
    Vec2 s = d - c;
    float rxs = (r.x * s.y - s.x * r.y);
    Vec2 cma = c - a;
    float t = (cma.x * s.y - s.x * cma.y) / rxs;
    float u = (cma.x * r.y - r.x * cma.y) / rxs;
    if (t >= 0 && t <= 1 && u >= 0 && u <= 1)
    {
        return { true, Vec2(a.x + t * r.x,a.y + t * r.y) };
    }

    return { false, Vec2(0,0) };
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 768), "Light");
    window.setFramerateLimit(60);

    Intersection inter;

    std::vector<sf::ConvexShape> convexes, shadedTriangles;
    std::vector<LineSegment> lineSegments;
    std::map<Vec2, float> angles;
    std::multimap<float, Vec2> orderedAngles;
    bool moveUp = false;
    bool moveDown = false;
    bool moveLeft = false;
    bool moveRight = false;

    sf::CircleShape sun(10);
    sun.setFillColor(sf::Color(255, 255, 0));
    sun.setOrigin(sun.getRadius(), sun.getRadius());
    sun.setPosition(window.getSize().x / 2, window.getSize().y / 2);

    //srand(time(0));

    for (int i = 0; i < 4; i++)
    {
        sf::ConvexShape convex;
        LineSegment ls;

        convex.setPointCount(3);

        switch (i)
        {
        case(0):
            convex.setPoint(0, sf::Vector2f(rand() % window.getSize().x / 2, rand() % window.getSize().y / 2));            
            convex.setPoint(1, sf::Vector2f(rand() % window.getSize().x / 2, rand() % window.getSize().y / 2));
            convex.setPoint(2, sf::Vector2f(rand() % window.getSize().x / 2, rand() % window.getSize().y / 2));

            ls.start = Vec2(convex.getPoint(0).x, convex.getPoint(0).y);
            ls.end = Vec2(convex.getPoint(1).x, convex.getPoint(1).y);
            lineSegments.push_back(ls);

            ls.end = Vec2(convex.getPoint(2).x, convex.getPoint(2).y);
            lineSegments.push_back(ls);

            ls.start = Vec2(convex.getPoint(1).x, convex.getPoint(1).y);
            lineSegments.push_back(ls);

            break;
        case(1):
            convex.setPoint(0, sf::Vector2f(window.getSize().x / 2 + rand() % window.getSize().x / 2, rand() % window.getSize().y / 2));
            convex.setPoint(1, sf::Vector2f(window.getSize().x / 2 + rand() % window.getSize().x / 2, rand() % window.getSize().y / 2));
            convex.setPoint(2, sf::Vector2f(window.getSize().x / 2 + rand() % window.getSize().x / 2, rand() % window.getSize().y / 2));

            ls.start = Vec2(convex.getPoint(0).x, convex.getPoint(0).y);
            ls.end = Vec2(convex.getPoint(1).x, convex.getPoint(1).y);
            lineSegments.push_back(ls);

            ls.end = Vec2(convex.getPoint(2).x, convex.getPoint(2).y);
            lineSegments.push_back(ls);

            ls.start = Vec2(convex.getPoint(1).x, convex.getPoint(1).y);
            lineSegments.push_back(ls);
            break;
        case(2):
            convex.setPoint(0, sf::Vector2f(rand() % window.getSize().x / 2, window.getSize().y / 2 + rand() % window.getSize().y / 2));
            convex.setPoint(1, sf::Vector2f(rand() % window.getSize().x / 2, window.getSize().y / 2 + rand() % window.getSize().y / 2));
            convex.setPoint(2, sf::Vector2f(rand() % window.getSize().x / 2, window.getSize().y / 2 + rand() % window.getSize().y / 2));

            ls.start = Vec2(convex.getPoint(0).x, convex.getPoint(0).y);
            ls.end = Vec2(convex.getPoint(1).x, convex.getPoint(1).y);
            lineSegments.push_back(ls);

            ls.end = Vec2(convex.getPoint(2).x, convex.getPoint(2).y);
            lineSegments.push_back(ls);

            ls.start = Vec2(convex.getPoint(1).x, convex.getPoint(1).y);
            lineSegments.push_back(ls);
            break;
        case(3):
            convex.setPoint(0, sf::Vector2f(window.getSize().x / 2 + rand() % window.getSize().x, window.getSize().y / 2 + rand() % window.getSize().y));
            convex.setPoint(1, sf::Vector2f(window.getSize().x / 2 + rand() % window.getSize().x, window.getSize().y / 2 + rand() % window.getSize().y));
            convex.setPoint(2, sf::Vector2f(window.getSize().x / 2 + rand() % window.getSize().x, window.getSize().y / 2 + rand() % window.getSize().y));

            ls.start = Vec2(convex.getPoint(0).x, convex.getPoint(0).y);
            ls.end = Vec2(convex.getPoint(1).x, convex.getPoint(1).y);
            lineSegments.push_back(ls);

            ls.end = Vec2(convex.getPoint(2).x, convex.getPoint(2).y);
            lineSegments.push_back(ls);

            ls.start = Vec2(convex.getPoint(1).x, convex.getPoint(1).y);
            lineSegments.push_back(ls);
            break;
        defaut:
            std::cout << "nesto se sjebalo";
        }
        
        convex.setFillColor(sf::Color(255, 0, 0));

        convexes.push_back(convex);

    }

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed)
            {
                switch (event.key.code)
                {
                case sf::Keyboard::W:
                    moveUp = true;
                    break;
                case sf::Keyboard::S:
                    moveDown = true;
                    break;
                case sf::Keyboard::A:
                    moveLeft = true;
                    break;
                case sf::Keyboard::D:
                    moveRight = true;
                    break;              
                default:
                    break;
                }
            }
            if (event.type == sf::Event::KeyReleased)
            {
                switch (event.key.code)
                {
                case sf::Keyboard::W:
                    moveUp = false;
                    break;
                case sf::Keyboard::S:
                    moveDown = false;
                    break;
                case sf::Keyboard::A:
                    moveLeft = false;
                    break;
                case sf::Keyboard::D:
                    moveRight = false;
                    break;
                default:
                    break;
                }
            }
        }
        window.clear();

        if (moveUp && sun.getPosition().y > 5)
        {
            sun.setPosition(sun.getPosition().x, sun.getPosition().y - 5);
        }

        if (moveDown && sun.getPosition().y < window.getSize().y)
        {
            sun.setPosition(sun.getPosition().x, sun.getPosition().y + 5);
        }

        if (moveLeft && sun.getPosition().x > 5)
        {
            sun.setPosition(sun.getPosition().x - 5, sun.getPosition().y);
        }

        if (moveRight && sun.getPosition().x < window.getSize().x)
        {
            sun.setPosition(sun.getPosition().x + 5, sun.getPosition().y);
        }

        angles.clear();

        for (auto c : convexes)
        {
            window.draw(c);
        }

        angles.clear();

        // add intersection points and angles

        for (auto c : convexes)
        {
            for (int p = 0; p < c.getPointCount();p++)
            {
                bool visible = true;
                for (auto ls : lineSegments)
                {
                    if (c.getPoint(p) == sf::Vector2f(ls.start.x, ls.start.y) || c.getPoint(p) == sf::Vector2f(ls.end.x, ls.end.y)) { continue; }
                    inter = checkIntersection(Vec2(sun.getPosition().x, sun.getPosition().y), Vec2(c.getPoint(p).x, c.getPoint(p).y),
                            Vec2(ls.start.x, ls.start.y), Vec2(ls.end.x, ls.end.y));
                    if (inter.result)
                    {
                        visible = false;
                    }
                }
                if (visible)
                {
                    float tanVal = atan2f(c.getPoint(p).y - sun.getPosition().y, c.getPoint(p).x - sun.getPosition().x);
                    angles[Vec2(c.getPoint(p).x, c.getPoint(p).y)] = tanVal;
                }
            }
        }      

        // add intersection points to corners of the screen if visible

        bool topLeftVisible = true;
        bool topRightVisible = true;
        bool bottomLeftVisible = true;
        bool bottomRightVisible = true;

        for (auto ls : lineSegments)
        {            
            inter = checkIntersection(Vec2(sun.getPosition().x, sun.getPosition().y), Vec2(0, 0),
                Vec2(ls.start.x, ls.start.y), Vec2(ls.end.x, ls.end.y));
            if (inter.result)
            {                
                topLeftVisible = false;
            }

            inter = checkIntersection(Vec2(sun.getPosition().x, sun.getPosition().y), Vec2(window.getSize().x, 0),
                Vec2(ls.start.x, ls.start.y), Vec2(ls.end.x, ls.end.y));
            if (inter.result)
            {
                topRightVisible = false;
            }

            inter = checkIntersection(Vec2(sun.getPosition().x, sun.getPosition().y), Vec2(0, window.getSize().y),
                Vec2(ls.start.x, ls.start.y), Vec2(ls.end.x, ls.end.y));
            if (inter.result)
            {
                bottomLeftVisible = false;
            }

            inter = checkIntersection(Vec2(sun.getPosition().x, sun.getPosition().y), Vec2(window.getSize().x, window.getSize().y),
                Vec2(ls.start.x, ls.start.y), Vec2(ls.end.x, ls.end.y));
            if (inter.result)
            {
                bottomRightVisible = false;
            }
        }

        if (topLeftVisible)
        {
            float tanVal = atan2f(0 - sun.getPosition().y, 0 - sun.getPosition().x);
            angles[Vec2(0,0)] = tanVal;
        }

        if (topRightVisible)
        {
            float tanVal = atan2f(0 - sun.getPosition().y, window.getSize().x - sun.getPosition().x);
            angles[Vec2(window.getSize().x, 0)] = tanVal;
        }

        if (bottomLeftVisible)
        {
            float tanVal = atan2f(window.getSize().y - sun.getPosition().y, 0 - sun.getPosition().x);
            angles[Vec2(0, window.getSize().y)] = tanVal;
        }

        if (bottomRightVisible)
        {
            float tanVal = atan2f(window.getSize().y - sun.getPosition().y, window.getSize().x - sun.getPosition().x);
            angles[Vec2(window.getSize().x, window.getSize().y)] = tanVal;
        }

        // multimap to order points

        orderedAngles.clear();

        for (auto a : angles)
        {
            // add aditional lines based on angles
            float angleTanP = a.second - 0.000001;
            float angleTanN = a.second + 0.000001;

            int sizeconst = 2000;

            Vec2 n(sun.getPosition().x + sizeconst * cosf(angleTanN), sun.getPosition().y + sizeconst * sinf(angleTanN));
            Vec2 p(sun.getPosition().x + sizeconst * cosf(angleTanP), sun.getPosition().y + sizeconst * sinf(angleTanP));

            for (auto ls : lineSegments)
            {
                
                inter = checkIntersection(Vec2(sun.getPosition().x, sun.getPosition().y), Vec2(n.x, n.y),
                    Vec2(ls.start.x, ls.start.y), Vec2(ls.end.x, ls.end.y));
                if (inter.result)
                {
                    n = inter.position;
                }

                inter = checkIntersection(Vec2(sun.getPosition().x, sun.getPosition().y), Vec2(p.x, p.y),
                    Vec2(ls.start.x, ls.start.y), Vec2(ls.end.x, ls.end.y));
                if (inter.result)
                {
                    p = inter.position;
                }             
            }

            orderedAngles.insert({ angleTanP, p });
            orderedAngles.insert({ a.second,a.first });
            orderedAngles.insert({ angleTanN, n });
        }        
        
        // set "light" triangles based on intersecting points

        shadedTriangles.clear();

        for (auto oait = orderedAngles.begin(); oait != orderedAngles.end(); oait++)
        {
            if (std::next(oait) != orderedAngles.end())
            {
                auto next = std::next(oait);

                sf::ConvexShape convex;

                convex.setPointCount(3);

                convex.setPoint(0, sun.getPosition());
                convex.setPoint(1, sf::Vector2f(oait->second.x, oait->second.y));
                convex.setPoint(2, sf::Vector2f(next->second.x, next->second.y));

                convex.setFillColor(sf::Color(255, 255, 255, 127));

                shadedTriangles.push_back(convex);

            }
            else
            {
                sf::ConvexShape convex;

                convex.setPointCount(3);

                convex.setPoint(0, sun.getPosition());
                convex.setPoint(1, sf::Vector2f(orderedAngles.begin()->second.x, orderedAngles.begin()->second.y));
                convex.setPoint(2, sf::Vector2f(oait->second.x, oait->second.y));

                convex.setFillColor(sf::Color(255, 255, 255, 127));

                shadedTriangles.push_back(convex);
            }
        }

        // draw "light" triangles

        for (auto st : shadedTriangles)
        {
            window.draw(st);
        }

        window.draw(sun);

        window.display();
    }

	return 0;
}