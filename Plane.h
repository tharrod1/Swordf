/**
 * @file Plane.h
 * @author Richard Case <johndoe27328@gmail.com>
 * @version 1.0
 *
 * @section LICENSE
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 3 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details at
 * https://www.gnu.org/copyleft/gpl.html
 *
 * @section DESCRIPTION
 *
 * The time class represents a plane that can store a 2D image.
 */

#include <GL/glut.h>

class Plane {
 private:
  
 public:
  GLfloat x, y, z,
    yr, xr, zr;
  
  Plane(char *path){
    //open image
  }

  Plane(char *path, GLfloat ix, GLfloat iy, GLfloat iz){
    Plane(path);
    x = ix;
    y = iy;
    z = iz;
  }

  Plane(char *path, GLfloat ix, GLfloat iy, GLfloat iz,
	GLfloat ixr, GLfloat iyr, GLfloat izr){
    Plane(path, ix, iy, iz);
    xr = ixr;
    yr = iyr;
    zr = izr;
  }

  void update(){
    //draw image at location
  }

  ~Plane(){
    //destroy image
  }
};
