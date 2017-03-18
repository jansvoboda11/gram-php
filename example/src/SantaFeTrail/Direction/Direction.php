<?php

namespace Example\SantaFeTrail\Direction;

use Example\SantaFeTrail\Point;

abstract class Direction
{
    /**
     * Move given point in direction.
     *
     * @param Point $point
     * @return Point
     */
    abstract public function move(Point $point);

    /**
     * Rotate direction clockwise.
     *
     * @return Direction
     */
    abstract public function rotateClockwise();

    /**
     * Rotate direction counterclockwise.
     *
     * @return Direction
     */
    abstract public function rotateCounterclockwise();
}
