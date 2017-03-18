<?php

namespace Example\SantaFeTrail\Direction;

use Example\SantaFeTrail\Point;

class LeftDirection extends Direction
{
    /**
     * Move given point in direction.
     *
     * @param Point $point
     * @return Point
     */
    public function move(Point $point)
    {
        return $point->decrementX();
    }

    /**
     * Rotate direction clockwise.
     *
     * @return Direction
     */
    public function rotateClockwise()
    {
        return new UpDirection();
    }

    /**
     * Rotate direction counterclockwise.
     *
     * @return Direction
     */
    public function rotateCounterclockwise()
    {
        return new DownDirection();
    }
}
