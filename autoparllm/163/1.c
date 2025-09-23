/*--------------------------------------------------------------------
  (C) Copyright 2006-2013 Barcelona Supercomputing Center
                          Centro Nacional de Supercomputacion

  This file is part of Mercurium C/C++ source-to-source compiler.

  See AUTHORS file in the top level directory for information
  regarding developers and contributors.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 3 of the License, or (at your option) any later version.

  Mercurium C/C++ source-to-source compiler is distributed in the hope
  that it will be useful, but WITHOUT ANY WARRANTY; without even the
  implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.  See the GNU Lesser General Public License for more
  details.

  You should have received a copy of the GNU Lesser General Public
  License along with Mercurium C/C++ source-to-source compiler; if
  not, write to the Free Software Foundation, Inc., 675 Mass Ave,
  Cambridge, MA 02139, USA.
--------------------------------------------------------------------*/
/*
<testinfo>
test_generator=(config/mercurium-ompss "config/mercurium-ompss-2
openmp-compatibility") test_compile_fail_nanos6_mercurium=yes
test_compile_fail_nanos6_imcc=yes
</testinfo>
*/
#include "omp.h"
#include <assert.h>
#include <omp.h>
#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main(int argc, char *argv[]) {
    int i;
    int s = 0;
    dummyMethod1();

#pragma omp parallel for private(i) reduction(+ : s)
    // #pragma rose_outline
    for (i = 0; i <= 99; i += 1) {
        s += i;
    }
    printf("%d\n", s);
    dummyMethod2();
    (((void)(sizeof(((s == 4950 ? 1 : 0))))), (({
         if (s == 4950)
             ;
         else
             __assert_fail("s == 4950",
                           "bsc-pm_nanox_success_parallel_for_slicer_01.c", 55,
                           __PRETTY_FUNCTION__);
     })));
    return 0;
}

int dummyMethod1() { return 0; }

int dummyMethod2() { return 0; }

int dummyMethod3() { return 0; }

int dummyMethod4() { return 0; }
