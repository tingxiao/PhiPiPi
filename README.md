# PhiPiPi Final State

## Process:
gamma p->pi^+pi^-K^+K^- p

phi is identified by fitting K+K- in each 50 MeV bin of M(pipiKK) spectrum.

## Root file:
e.g. tree_pippimkpkm__B4_030274.root

## Event selections:

### At initialization:
* Time of flight in SYS_NULL, |delta_t| < 2 ns (line 41)

### Looping over combos:
* At least 7 tracks (line 446)
* dE/dx cut for proton (line 372, 598)
* Kinematic fit confidence level > 0 (line 638)
* Missing mass squared < 0.02 GeV (line 696)
* 1.4 < M(phipipi) < 3.5 Gev (line 703)
* Track quality cut (line 715)
* Time of flight for K+, K-, |delta_t| < 0.3 ns (line 784, 859)
* Time of flight for p, pi+, pi-, |delta_t| < 0.5 ns (line 935, 1002, 1066)
