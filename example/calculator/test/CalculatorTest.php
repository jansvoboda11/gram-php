<?php

use Examples\Calculator;
use PHPUnit\Framework\TestCase;

class CalculatorTest extends TestCase
{
    public function test_it_returns_integer()
    {
        $calculator = new Calculator();

        self::assertEquals(0, $calculator->inc(-1));
    }

    public function test_it_fails()
    {
        $calculator = new Calculator();

        self::assertEquals(2, $calculator->inc(1));
    }

    public function test_it_passes()
    {
        $calculator = new Calculator();

        self::assertEquals(3, $calculator->inc(2));
    }

    public function test_it_fails_again()
    {
        $calculator = new Calculator();

        self::assertGreaterThan(42, $calculator->inc(41));
    }
}
