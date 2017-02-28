<?php

use PHPUnit\Framework\AssertionFailedError;
use PHPUnit\Framework\ExpectationFailedException;
use PHPUnit\Framework\Test;
use PHPUnit\Util\Log\JUnit;

class LoggingListener extends JUnit
{
    /**
     * A failure occurred.
     *
     * @param Test                 $test
     * @param AssertionFailedError $e
     * @param float                $time
     */
    public function addFailure(Test $test, AssertionFailedError $e, $time)
    {
        if (!$e instanceof ExpectationFailedException || !$e->getComparisonFailure()) {
            return;
        }

        $comparisonFailure = $e->getComparisonFailure();

        $fault = $this->document->createElement('failure');

        $expected = $this->document->createElement(
            'expected', serialize($comparisonFailure->getExpected())
        );

        $actual = $this->document->createElement(
            'actual', serialize($comparisonFailure->getActual())
        );

        $fault->appendChild($expected);
        $fault->appendChild($actual);

        $this->currentTestCase->appendChild($fault);

        $this->testSuiteFailures[$this->testSuiteLevel]++;
    }
}
