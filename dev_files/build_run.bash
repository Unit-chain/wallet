#!/bin/bash

(cd ../build-Unit-Desktop-Debug; cmake --build .; make; ./UnitWallet)
