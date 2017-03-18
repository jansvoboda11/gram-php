<?php

namespace Example\SantaFeTrail;

use InvalidArgumentException;

class Trail
{
    /**
     * @var Grid
     */
    private $grid;

    /**
     * @var Point[]
     */
    private $food = [];

    /**
     * Trail constructor.
     *
     * @param Grid $grid
     */
    public function __construct(Grid $grid)
    {
        $this->grid = $grid;
    }

    /**
     * Place food on the trail.
     *
     * @param Point $point
     */
    public function placeFood(Point $point)
    {
        if (!$this->fits($point)) {
            throw new InvalidArgumentException("Given point does not fit on the trail grid.");
        }

        if (!$this->hasFoodAt($point)) {
            $this->food[] = $point;
        }
    }

    /**
     * Determine if trail fits given point.
     *
     * @param Point $point
     * @return bool
     */
    public function fits(Point $point)
    {
        return $this->grid->fits($point);
    }

    /**
     * Determine if there is food on trail at the given point.
     *
     * @param Point $point
     * @return bool
     */
    public function hasFoodAt(Point $point)
    {
        return in_array($point, $this->food);
    }

    /**
     * Remove food from the given point on trail.
     *
     * @param Point $point
     */
    public function pickUpFoodAt(Point $point)
    {
        if (!$this->hasFoodAt($point)) {
            throw new InvalidArgumentException("Trail does not have food at given point.");
        }

        $this->food = array_filter($this->food, function (Point $foodPoint) use ($point) {
            return $foodPoint != $point;
        });
    }

    /**
     * Get number of food pieces on trail.
     *
     * @return int
     */
    public function foodCount()
    {
        return count($this->food);
    }
}
