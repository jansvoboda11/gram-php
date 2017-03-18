<?php

namespace Example\SantaFeTrail;

use Example\SantaFeTrail\Direction\Direction;
use InvalidArgumentException;

class Point
{
    /**
     * @var int
     */
    private $x;

    /**
     * @var int
     */
    private $y;

    /**
     * Point constructor.
     *
     * @param int $x
     * @param int $y
     */
    public function __construct(int $x, int $y)
    {
        if ($x < 0 || $y < 0) {
            throw new InvalidArgumentException("Point cannot have negative coordinates.");
        }

        $this->x = $x;
        $this->y = $y;
    }

    /**
     * Increment X coordinate by given offset.
     *
     * @param int $offset
     * @return Point
     */
    public function incrementX(int $offset = 1)
    {
        return new Point($this->x + $offset, $this->y);
    }

    /**
     * Increment Y coordinate by given offset.
     *
     * @param int $offset
     * @return Point
     */
    public function incrementY(int $offset = 1)
    {
        return new Point($this->x, $this->y + $offset);
    }

    /**
     * Decrement X coordinate by given offset.
     *
     * @param int $offset
     * @return Point
     */
    public function decrementX(int $offset = 1)
    {
        return $this->incrementX(-$offset);
    }

    /**
     * Decrement X coordinate by given offset.
     *
     * @param int $offset
     * @return Point
     */
    public function decrementY(int $offset = 1)
    {
        return $this->incrementY(-$offset);
    }

    /**
     * Determine whether the point fits in given dimensions.
     *
     * @param int $x
     * @param int $y
     * @return bool
     */
    public function fitsIn(int $x, int $y)
    {
        return $this->x < $x && $this->y < $y;
    }

    /**
     * Move point in given direction.
     *
     * @param Direction $direction
     * @return Point
     */
    public function moveIn(Direction $direction)
    {
        return $direction->move($this);
    }
}
