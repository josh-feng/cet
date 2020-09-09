# cet
Computational Experiment Toolbox is based on Lua.

The initial gui will be based on FLTK (~IUP~),
and [moonFLTK](https://github.com/stetre/moonfltk) is used.
Extension to web browser (html/xhtml) is also in the long term plan.
However, javascript and other web support scripting languages might be employed.

CET lua module shall be good for lua >= 5.3.

# Scope and Plan

- computational experiment toolbox : cet (gsl)
    - func: special functions
        binom
        multinom
        normal
        hermite
        gamma
        beta
        bessel
        laguerre
        legendre
        sph: spheric harmonic
        poisson
        doc: brief usage summary
    - la: linear algebra (blas-lapack-atlas)
    - stat: statistics
    - z: complex number
    - alg: symbolic

    - implementation:
        - wedget -> IUP
            ref: https://idmoz.org/Computers/Software/Operating_Systems/Graphic_Subsystems/Toolkits/FLTK
            - template
                - table -> require 'cet' {}
            - audio/video
            - 2D/3D
        - c/c++ api
        - network (SSL)
        - documentation

# GUI

- fltk4lua was the inital choice, but dropped due to its partial implementation in fltk
- IUP was the next choice, but dropped due to its readiness on several
platforms (MacOS, debian, etc)
- [moonFLTK](https://github.com/stetre/moonfltk)
is fairly comprehensive, so we will base on it
to develop an abstract layer.

# Numerical Package

- GSL
- Lapack

# Distributive (Network)

- TODO
