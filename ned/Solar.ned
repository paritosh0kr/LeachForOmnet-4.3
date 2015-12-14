//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

package ned;

module Solar
{
    parameters:
        int numNodes;
        double trRange;
        int rounds;
        int frames;
        int solarOn;
        double sunDuration;
        int sunNodes;
        double xMax;
        double yMax;
        @display("bgi=maps/world,s;bgb=,,#0080FF");
    submodules:
        bs: BS {
            parameters:
                id = 1;
                xpos = xMax/2;
                ypos = yMax/2;
                @display("i=device/antennatower;is=vl");
        }
        node[numNodes]: Node {
            parameters:
                energy = intuniform(499900, 500000);
                sunstart = intuniform(20, (numNodes/sunNodes)*sunDuration);
                //energy = energy,
                id = index+2;
                xpos = intuniform(0, xMax);
                ypos = intuniform(0, yMax);

                @display("is=vl;p=156,100");
        }
    connections:

}
