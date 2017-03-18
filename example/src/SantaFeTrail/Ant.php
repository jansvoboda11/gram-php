<?php

namespace Example\SantaFeTrail;

use Example\SantaFeTrail\Direction\Direction;
use Exception;

class Ant
{
    /**
     * @var Brain
     */
    private $brain;

    /**
     * @var Trail
     */
    private $trail;

    /**
     * @var Point
     */
    private $position;

    /**
     * @var Direction
     */
    private $direction;

    /**
     * @var int
     */
    private $foodCount = 0;

    /**
     * @var int
     */
    private $spentTime = 0;

    /**
     * Ant constructor.
     *
     * @param Brain $brain
     * @param Trail $trail
     * @param Point $position
     * @param Direction $direction
     */
    public function __construct(Brain $brain, Trail $trail, Point $position, Direction $direction)
    {
        $this->brain = $brain;
        $this->trail = $trail;
        $this->position = $position;
        $this->direction = $direction;
    }

    /**
     * Collect as many pieces of food as fast as possible using given brain.
     *
     * @param int $timeLimit
     */
    public function collect(int $timeLimit)
    {
        $foodCount = $this->trail->foodCount();

        while ($this->shouldKeepCollecting($foodCount, $timeLimit)) {
            $this->brain->control($this);
        }
    }

    /**
     * Determine if ant should keep collecting food.
     *
     * @param int $foodCount
     * @param int $timeLimit
     * @return bool
     */
    private function shouldKeepCollecting(int $foodCount, int $timeLimit)
    {
        return $this->foodCount < $foodCount && $this->spentTime < $timeLimit;
    }

    /**
     * Get number of collected food pieces.
     *
     * @return int
     */
    public function foodPiecesCollected()
    {
        return $this->foodCount;
    }

    /**
     * Determine if there is food ahead.
     *
     * @return bool
     */
    public function foodAhead()
    {
        $this->spentTime += 1;

        try {
            $pointAhead = $this->position->moveIn($this->direction);
        } catch (Exception $exception) {
            return false;
        }

        if (!$this->trail->fits($pointAhead)) {
            return false;
        }

        return $this->trail->hasFoodAt($pointAhead);
    }

    /**
     * Turn left.
     */
    public function turnLeft()
    {
        $this->spentTime += 1;

        $this->direction = $this->direction->rotateCounterclockwise();
    }

    /**
     * Turn right.
     */
    public function turnRight()
    {
        $this->spentTime += 1;

        $this->direction = $this->direction->rotateClockwise();
    }

    /**
     * Make a step.
     */
    public function move()
    {
        $this->spentTime += 1;

        $this->position = $this->position->moveIn($this->direction);

        if ($this->trail->hasFoodAt($this->position)) {
            $this->trail->pickUpFoodAt($this->position);

            $this->foodCount += 1;
        }
    }
}
