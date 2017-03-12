<?php

use Example\Calculator;
use PHPUnit\Framework\TestCase;

class CalculatorTest extends TestCase
{
    public function test_it_rejects_negative_number()
    {
        self::assertEquals(null, Calculator::increment(-42));
    }

    public function test_it_increments_zero()
    {
        self::assertEquals(1, Calculator::increment(0));
    }

    public function test_it_increments_one()
    {
        self::assertEquals(2, Calculator::increment(1));
    }

    public function test_it_increments_two()
    {
        self::assertEquals(3, Calculator::increment(2));
    }

    public function test_it_produces_the_answer_to_the_ultimate_question_of_life_the_universe_and_everything()
    {
        self::assertEquals(42, Calculator::increment(41));
    }
}
