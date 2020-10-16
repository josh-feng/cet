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
    - audio:
    - video:
        - image: png, jpg, svg
        - film: avi, mp4
    - network:
        - socket:

# GUI

- fltk4lua was the inital choice, but dropped due to its partial implementation in fltk
- IUP was the next choice, but dropped due to its readiness on several
platforms (MacOS, debian, etc)
- [moonFLTK](https://github.com/stetre/moonfltk)
is fairly comprehensive, so we will base on it
to develop an abstract layer.

hello world

```lua
local wb = gui.new -- workbench
{ ['.'] = 'window'; xywh = {340, 180}; label = 'Hello';
  scale = true;
  { ['.'] = 'box'; xywh = {20, 40, 300, 100}; label = 'Hello World!';
    labelfont = gui.BOLD + gui.ITALIC;
    labelsize = 36;
    labeltype = 'shadow';
    box = 'up';
  };
}

wb:show(arg[0], arg)
return fl.run()
```

adjuster

```lua
local wb = gui.new -- workbench
{ ['.'] = 'double_window'; w = 320; h = 100; label = arg[0];
  { ['.'] = 'box'; x = 20; y = 30; w = 80; h = 25; label = 'down box';
    bg = 'WHITE'; box = 'down';
  };
  { ['.'] = 'adjuster'; x = 20 + 80; y = 30; w = 3 * 25; h = 25;
  };
  { ['.'] = 'box'; x = 20 + 80 + 4 * 25; y = 30; w = 80; h = 25; label = 'down box';
    bg = 'WHITE'; box = 'down';
  };
  { ['.'] = 'adjuster'; x = 20 + 80 + 4 * 25 + 80; y = 10; w = 25; h = 3 * 25;
  };
}

function adjcb(adjuster, box)
   box:label(adjuster:format())
   box:redraw()
end

wb[2]:callback {adjcb, wb[1]}
wb[2]:do_callback() -- wb[1])
wb[4]:callback {adjcb, wb[3]}
wb[4]:do_callback() -- wb[3])

wb:show(arg[0], arg)
return fl.run()
```

# Numerical Package

- GSL
- Lapack

# Distributive (Network)

- TODO

# Archive

- TekUI
    - https://github.com/sirkha/tekUI
    - http://www.schulze-mueller.de/products_tekui.html
    - http://tekui.neoscientists.org/
