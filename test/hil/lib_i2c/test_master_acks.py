# Copyright 2014-2021 XMOS LIMITED.
# This Software is subject to the terms of the XMOS Public Licence: Version 1.
import Pyxsim as px
import pytest
from i2c_master_checker import I2CMasterChecker

stop_args = {"stop": "stop",
             "no_stop": "no_stop"}
             
@pytest.mark.parametrize("stop", stop_args.values(), ids=stop_args.keys())
def test_master_acks(build, capfd, stop):

    # It is assumed that this is of the form <arbitrary>/bin/<unique>/.../<executable>.xe,
    # and that <arbitrary> contains the CMakeLists.txt file for all test executables.
    binary = f'i2c_master_test/bin/ack_{stop}/i2c_master_test_tx_only_{stop}.xe'

    checker = I2CMasterChecker("tile[0]:XS1_PORT_1A",
                               "tile[0]:XS1_PORT_1B",
                               tx_data = [0x99, 0x3A, 0xff],
                               expected_speed = 400,
                               ack_sequence=[True, True, True,
                                             True, True, False,
                                             False, True])

    tester = px.testers.PytestComparisonTester(f'expected/ack_test_{stop}.expect',
                                                regexp = True,
                                                ordered = True)

    sim_args = ['--weak-external-drive']

    # The environment here should be set up with variables defined in the 
    # CMakeLists.txt file to define the build

    build(directory = binary, 
            env = {"STOPS":stop, "ACK_TEST":True},
            bin_child = f"ack_{stop}")

    px.run_with_pyxsim(binary,
                    simthreads = [checker],
                    simargs = sim_args)

    # The first two lines of this test are not reflected in the expectation file
    # and vary based on the test; cut them out.
    outcapture = capfd.readouterr().out.split("\n")[2:]

    tester.run(outcapture)
