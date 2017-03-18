<?php

namespace Example\SantaFeTrail\Direction;

use Example\SantaFeTrail\Point;

class DownDirection extends Direction
{
    /**
     * Move given point in direction.
     *
     * @param Point $point
     * @return Point
     */
    public function move(Point $point)
    {
        return $point->incrementY();
    }

    /**
     * Rotate direction clockwise.
     *
     * @return Direction
     */
    public function rotateClockwise()
    {
        return new LeftDirection();
    }

    /**
     * Rotate direction counterclockwise.
     *
     * @return Direction
     */
    public function rotateCounterclockwise()
    {
        return new RightDirection();
    }
}
