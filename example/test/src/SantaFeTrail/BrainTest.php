<?php

use Example\SantaFeTrail\Ant;
use Example\SantaFeTrail\Brain;
use Example\SantaFeTrail\Direction\LeftDirection;
use Example\SantaFeTrail\Grid;
use Example\SantaFeTrail\Point;
use Example\SantaFeTrail\Trail;
use PHPUnit\Framework\TestCase;

class BrainTest extends TestCase
{
    public function test_it_collects_all_food_pieces()
    {
        $brain = new Brain();

        $grid = new Grid(5, 5);
        $trail = new Trail($grid);
        $trail->placeFood(new Point(0, 1));
        $trail->placeFood(new Point(0, 2));
        $trail->placeFood(new Point(1, 2));
        $trail->placeFood(new Point(2, 2));
        $trail->placeFood(new Point(2, 3));

        $start = new Point(0,0);

        $direction = new LeftDirection();

        $ant = new Ant($brain, $trail, $start, $direction);

        $ant->collect(400);

        self::assertEquals(5, $ant->foodPiecesCollected());
    }
}
