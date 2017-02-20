<?php

use Examples\Calculator;
use PHPUnit\Framework\TestCase;

class CalculatorTest extends TestCase
{
    public function test_it_returns_integer()
    {
        $calculator = new Calculator();

        self::assertEquals(0, $calculator->run());
    }
}
