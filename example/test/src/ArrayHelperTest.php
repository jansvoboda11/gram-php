<?php

use Example\ArrayHelper;
use PHPUnit\Framework\TestCase;

class ArrayHelperTest extends TestCase
{
    public function test_it_filters_empty_array()
    {
        $array = [];

        $filtered = ArrayHelper::filter($array, function (int $item) {
            return $item > 0;
        });

        self::assertEquals([], $filtered);
    }

    public function test_it_filters_array_with_no_acceptable_items()
    {
        $array = [-10, -5, -3, -1];

        $filtered = ArrayHelper::filter($array, function (int $item) {
            return $item > 0;
        });

        self::assertEquals([], $filtered);
    }

    public function test_it_filters_array_with_some_acceptable_items()
    {
        $array = [-10, -5, -3, -1, 1, 3, 5, 10];

        $filtered = ArrayHelper::filter($array, function (int $item) {
            return $item > 0;
        });

        self::assertEquals([1, 3, 5, 10], $filtered);
    }

    public function test_it_filters_array_with_all_items_acceptable()
    {
        $array = [1, 20, 42];

        $filtered = ArrayHelper::filter($array, function (int $item) {
            return $item > 0;
        });

        self::assertEquals([1, 20, 42], $filtered);
    }
}