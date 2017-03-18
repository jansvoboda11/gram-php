<?php

namespace Example\SantaFeTrail;

class Grid
{
    /**
     * @var int
     */
    private $xSize;

    /**
     * @var int
     */
    private $ySize;

    /**
     * Grid constructor.
     *
     * @param int $xSize
     * @param int $ySize
     */
    public function __construct(int $xSize, int $ySize)
    {
        $this->xSize = $xSize;
        $this->ySize = $ySize;
    }

    /**
     * Determine if the given point fits on the grid.
     *
     * @param Point $point
     * @return bool
     */
    public function fits(Point $point)
    {
        return $point->fitsIn($this->xSize, $this->ySize);
    }
}
