#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
/*
 * This file is part of the Score-P software (http://www.score-p.org)
 *
 * Copyright (c) 2009-2011,
 * RWTH Aachen University, Germany
 *
 * Copyright (c) 2009-2011,
 * Gesellschaft fuer numerische Simulation mbH Braunschweig, Germany
 *
 * Copyright (c) 2009-2011,
 * Technische Universitaet Dresden, Germany
 *
 * Copyright (c) 2009-2011,
 * University of Oregon, Eugene, USA
 *
 * Copyright (c) 2009-2011, 2014
 * Forschungszentrum Juelich GmbH, Germany
 *
 * Copyright (c) 2009-2011,
 * German Research School for Simulation Sciences GmbH, Juelich/Aachen, Germany
 *
 * Copyright (c) 2009-2011,
 * Technische Universitaet Muenchen, Germany
 *
 * This software may be modified and distributed under the terms of
 * a BSD-style license. See the COPYING file in the package base
 * directory for details.
 *
 * Testfile for automated testing of OPARI2
 *
 *
 * @brief Tests user instrumentation directives and selective instrumentation.
 */

int main() {
    int i;
    int b = 1;

    i = 1;
    dummyMethod3();
#pragma omp parallel for reduction(+ : b)
    // #pragma rose_outline
    for (i = 0; i < 2; ++i)
        b = b + i;
    dummyMethod4();

    dummyMethod1();
#pragma omp parallel for reduction(+ : b)
    // #pragma rose_outline
    for (i = 0; i < 2; ++i)
        b = b + i;
    printf("%d", b);
    dummyMethod2();

    i = 3;

    if (b) {
        return 0;
    }

    {
        i = 4;
        i = 5;
    }

    if (b) {
        return 0;
    }

    return 0;
}
int dummyMethod1() { return 0; }
int dummyMethod2() { return 0; }
int dummyMethod3() { return 0; }
int dummyMethod4() { return 0; }