function run(ri, rj, chgi, chgj) result (e)
implicit none
double precision,intent(in) :: ri(3)
double precision,intent(in) :: rj(3)
double precision,intent(in) :: chgi
double precision,intent(in) :: chgj
double precision :: e
double precision :: dx, dy, dz
dx = ri(1) - rj(1)
dy = ri(2) - rj(2)
dz = ri(3) - rj(3)
e = chgi*chgj / sqrt(dx*dx+dy*dy+dz*dz)
end function
