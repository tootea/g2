
c/*****************************************************************************
c**  This is part of the g2 library
c**  Copyright (C) 1998  Ljubomir Milanovic & Horst Wagner
c**
c**  This program is free software; you can redistribute it and/or modify
c**  it under the terms of the GNU General Public License (version 2) as
c**  published by the Free Software Foundation.
c**
c**  This program is distributed in the hope that it will be useful,
cc**  but WITHOUT ANY WARRANTY; without even the implied warranty of
c**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
cc**  GNU General Public License for more details.
c**
c**  You should have received a copy of the GNU General Public License
c**  along with this program; if not, write to the Free Software
c**  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
c******************************************************************************/


	program main
	implicit none
	integer ndev
	parameter (ndev=5)
	integer  i, j, d, c, dev(0:ndev)
	data dev/-1,ndev*-1/
	character str*256
	real*8 pts(0:10)
	real*4 y
	include 'penguin.inc'
c	integer image(64)
c	data image/
c     & 0, 0, 2, 2, 2, 2, 0, 0,
c     & 0, 2, 0, 0, 0, 0, 2, 0,
c     & 2, 0, 3, 0, 0, 3, 0, 2,
c     & 2, 0, 0, 0, 0, 0, 0, 2,
c     & 2, 3, 0, 0, 0, 0, 3, 2,
c     & 2, 0, 3, 3, 3, 3, 0, 2,
c     & 0, 2, 0, 0, 0, 0, 2, 0,
c     & 0, 0, 2, 2, 2, 2, 0, 0 /
c /*open virtual device */
	call g2OpenVD(d)
	print*,"Adding.. VD=",d
    
#ifdef DO_PS
	str='g2testf.ps'
	str(11:11)=char(0)
	call g2openps(dev(0),str, 4, 0)
	print*,"..PS=",dev(0)
	call g2attach(d,dev(0))
#endif
#ifdef DO_X11
	call g2openx11(dev(1),775, 575)
	print*,"..X11=",dev(1)
	call g2attach(d,dev(1))
#endif
#ifdef DO_GIF
	str='g2testf.gif'
	str(12:12)=char(0)
	call g2opengif(dev(2),str, 775, 575)
	print*,"..GIF=",dev(2)
	call g2attach(d,dev(2))
#endif
	call g2AutoFlush(d,0)

c#      call g2coorsys(d, 775., 575., -0.75, -1.0)

	do i=0,27
	 call g2Pen(d, i)
	 call g2FilledCircle(d, float(i*20+10), 10., 10.) 
	 call g2Pen(d, 1)
	 call g2Circle(d, float(i*20+10), 10., 10.)
	 write(str(1:4),'(i3,a1)') i,char(0)
	 call g2String(d, float(i*20+7), 21., str(1:4))
	enddo
    
    	do j=0,ndev
	 if(dev(j).gt.0) then
	  do i=0,64
	   call g2Move(dev(j), float(2*i+575), 5.)
	   call g2Ink(c,dev(j), float(i)/64., 0., 0.)
	   call g2Pen(dev(j), c)
	   call g2LineR(dev(j), 0., 20.)
	   call g2Ink(c,dev(j), 0., float(i)/64., 0.)
	   call g2Pen(dev(j), c )
	   call g2LineR(dev(j), 10., 20.)
	   call g2Ink(c,dev(j), 0., 0., float(i)/64.)
	   call g2Pen(dev(j), c)
	   call g2LineR(dev(j), -10., 20.)
	  enddo
	 endif
	enddo
	call g2pen(d, 1)
	call g2line(d, 200., 50., 350., 50.)
	call g2line(d, 200., 48., 350., 48.)
	call g2line(d, 200., 46., 350., 46.)
	call g2line(d, 200., 46., 200., 75.)
	call g2line(d, 198., 46., 198., 75.)
	call g2line(d, 196., 46., 196., 75.)
	str="012abcABC#())(\\-+~*!$%&"//char(0)
	call g2string(d, 200., 50., str)
    
    	call g2pen(d, 1)
    	do i=1,25
	 call g2line(d, 15., float(i*20+50), 15., float(i*20+50+i))
	 call g2fontsize(d, 12.)
	 write(str(1:3),'(i2,a1)') i,char(0)
	 call g2string(d, 20., float(i*20+50), str)
	 call g2fontsize(d, float(i))
	 str='Hello, world!'//char(0)
	 call g2string(d, 40., float(i*20+50), str)
	enddo


	call g2plot(d, 150., 70.)
	call g2line(d, 147., 68., 153., 68.)
		
       y=100.
	call g2line(d, 100., y, 150., y+50.)
	call g2triangle(d, 150., y, 250., y, 200., y+50.)
	call g2rectangle(d, 300., y, 400., y+50.)
	call g2circle(d, 450., y+25., 25.)
	call g2ellipse(d, 550., y+25., 45., 25.)
	call g2arc(d, 650., y+25., 25., 45., 90., 360.)
    
       y=200.
	call g2filledtriangle(d, 150., y, 250., y, 200., y+50.)
	call g2filledrectangle(d, 300., y, 400., y+50.)
	call g2filledcircle(d, 450., y+25., 25.)
	call g2filledellipse(d, 550., y+25., 45., 25.)
	call g2filledarc(d, 650., y+25., 25., 45., 90., 360.)


        y=300.
        pts(0)=150.
         pts(1)=y
        pts(2)=175.
         pts(3)=y+100.
        pts(4)=200.
         pts(5)=y
        pts(6)=225.
         pts(7)=y+100.
        pts(8)=250.
         pts(9)=y
	call g2polyline(d, 5, pts(0))
    
   	 pts(0)=300.
   	  pts(1)=y
   	 pts(2)=350.
   	  pts(3)=y
   	 pts(4)=375.
   	  pts(5)=y+50.
   	 pts(6)=325.
   	  pts(7)=y+90.
   	 pts(8)=275.
   	  pts(9)=y+50.
	call g2polygon(d, 5, pts(0))

    	pts(0)=450.
    	 pts(1)=y
    	pts(2)=500.
    	 pts(3)=y
    	pts(4)=525.
    	 pts(5)=y+50.
    	pts(6)=475.
    	 pts(7)=y+90.
    	pts(8)=425.
    	 pts(9)=y+50.
	call g2filledpolygon(d, 5, pts(0))

    
	call g2image(d, 55., 50., 53, 62, penguin)
	call g2image(d, 75., 130., 53, 62, penguin)
	call g2pen(d, 1)
    
	call g2line(d, 225., 448., float(200+19*25), 448.)
    	do i=1,20
    	 call g2pen(d,i+1)
	 call g2linewidth(d, float(i))
	 call g2move(d, float(200+i*25), 450.)
	 call g2lineto(d, float(200+i*25), 550.)
       enddo
	call g2pen(d,1)
    
	call g2linewidth(d, 5.)
      do i=1,10
	pts(0)=float(1*i)
	pts(1)=float(2*i)
	pts(2)=float(3*i)
	call g2setdash(d, 3, pts(0))
	call g2line(d, 550., float(300+i*8), 750., float(350+i*8)) 
      enddo

	call g2setdash(d, 0, pts(0))
	call g2linewidth(d, 5.)
	call g2arc(d, 740., 180., 25., 100., -45.+15., -45.-15.)
	call g2filledarc(d, 740., 180., 12., 50., -45.+15., -45.-15.)
c----------------------------------------------------------
	call g2flush(d)
	print*,"Done...(Enter)"
	read(*,'(a)') str
	call g2close(d)
	end
c #eof#





