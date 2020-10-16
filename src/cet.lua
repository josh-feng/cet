#!/usr/bin/env lua
-- MIT license
-- Goal: computational experiment toolbox : cet (gsl)
-- l. gsl
--      - la: linear algebra (blas-lapack-atlas)
--      - statistics
--    func: special functions
--      binom
--      multinom
--      normal
--      hermite
--      gamma
--      beta
--      bessel
--      laguerre
--      legendre
--      sph: spheric harmonic
--      poisson
--      doc: brief usage summary
-- 2. document (tex/markdown)
-- 3. wedget -> moonFLTK
--          - audio/video
--          - 2D/3D
--      - network (SSL)
--      - documentation
-- 4. network / parallel
-- 5. PETSc
--      - SLEPc --> C++
-- 6. alg: symbolic (Maxima)
-- 7. sqlite
-- ref:
--  GSL shell: http://www.nongnu.org/gsl-shell/#
--  https://www.gnu.org/software/gsl/doc/html/intro.html
--  Lua graph-toolkit: https://github.com/franko/graph-toolkit
--  https://en.wikipedia.org/wiki/List_of_numerical_libraries
-- =============================================================== --
-- computational experiment toolbox : cet (gsl)
--   func: special functions
--       binom
--       multinom
--       normal
--       hermite
--       gamma
--       beta
--       bessel
--       laguerre
--       legendre
--       sph: spheric harmonic
--       poisson
--       doc: brief usage summary
--   la: linear algebra (blas-lapack-atlas)
--   stat: statistics
--   z: complex number
--   alg: symbolic
--
--   implementation:
--       - wedget -> fltk
--           - template
--               - table -> require 'cet' {}
--           - audio/video
--           - 2D/3D
--       - c/c++ api
--       - network (SSL)
--       - documentation
--
-- sql: database
--   chem: chemical
--   high: high energy
--   cm: condense matter
-- fdm:
-- fem:
-- fvm:
-- cfd: compuational fluid dynamics
-- pde:
-- =============================================================== --
-- widget (sub)
-- ├─ box (sub)
-- ├─ button (sub)
-- │   ├─ light_button
-- │   │   ├─ check_button
-- │   │   ├─ radio_light_button
-- │   │   └─ round_button
-- │   │       └─ radio_round_button
-- =============================================================== --
local cetcore = require 'cetcore' -- math obj
local class = require 'pool'

local cet = {}
local cetmeta = {
    qtrn   = cetcore.qtrn;   -- complex or quaternion
    colvec = cetcore.colvec; -- vector (column vector)
    rowvec = cetcore.rowvec; -- vector (row vector)
    matrix = cetcore.matrix; -- matrix -- b = cet.spm() -- sparse matrix
    domain = cetcore.domain; -- cw complex space
    tensor = cetcore.tensor; -- tensor field on domain

    --- use luadoc
    help = function (cmd)
    end;

    gui = class {
        wgt = false;

        ['<'] = function (o, workbench)
            -- if workbench then o.wgt = gui(workbench) end
        end;

        { -- data/gui operation
            __add = function (o1, o2) -- dock o2 to o1

            end;
        }
    };
}
setmetatable(cet, {
    __index = cetmeta;
    __metatable = true;
})

-- position/numerical index
z = cet.qtrn(0, 1) -- complex
-- q = cet.qtn(0, 1, 0, 0) -- quaternion
-- a = cet.vec() -- vector (row vector)
-- b = cet.mat() -- matrix
-- c = cet.tsr() -- tensor
-- b = cet.spm() -- sparse matrix

-- rawget / rawset -- file: reader/writer binary: load/dump
-- z.Re, z.Im
-- q[0] = 1; q[1] = 2; q[2] = 3; a[3] = 4 -- index 1 to n

return cet
-- vim: ts=4 sw=4 sts=4 et foldenable fdm=marker fmr={{{,}}} fdl=1
