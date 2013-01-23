      PROGRAM fortranmatmul

          IMPLICIT NONE
          integer i, j
          !integer nargs
          !character arg*8
          integer, parameter :: N = 2

          !parameter nargs = iargs()
          !do i = 0,nargs 
          !    call getarg(i, arg) 
          !    print '(a)', arg 
          !end do

          !if (nargs == 2) then
          !    call getarg(2, arg)
          !    read(s,*) N 
          !end if

          real :: a(N,N) = RESHAPE((/(2.0, i=0,N*N, 1)/),(/N,N/))
          real :: b(N,N) = RESHAPE((/(i, i=0,N*N, 1)/),(/N,N/))
          real :: c(N,N)

          write(*,*) 'Matrix [a]'
          do i=1,N
          write(*,1000) (a(i,j),j=1,N)
          enddo
          write(*,*)

          write(*,*) 'Matrix [b]'
          do i=1,N
          write(*,1000) (b(i,j),j=1,N)
          enddo
          write(*,*)

          c = matmul(a, b)
          write(*,*) 'Matrix [c] = [a] x [b]'
          do i = 1,N
          write(*,1000) (c(i,j),j=1,N)
          enddo

1000  FORMAT(1x,1P10E14.6)

      END PROGRAM fortranmatmul
