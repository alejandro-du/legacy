/*
 * Created on 20/07/2005
 *
 * TODO To change the template for this generated file go to
 * Window - Preferences - Java - Code Style - Code Templates
 */
package gravity1;


/**
 * @author Compaq
 * 
 * TODO To change the template for this generated type comment go to
 * Window - Preferences - Java - Code Style - Code Templates
 */

public class Simulation
{
    private int width;
    private int height;
    
    public Simulation(int width, int height)
    {
        this.width = width;
        this.height = height;
        
        balls = new Ball[3];
        
        balls[0] = new Ball(((width / balls.length) / 2) * 1 - 15, 47, 30, 0);
        balls[1] = new Ball(((width / balls.length) / 2) * 3 - 15, 60, 30, 0);
        balls[2] = new Ball(((width / balls.length) / 2) * 5 - 15, 31, 30, 0);
    }
    
    public void update()
    {
        for(int i = 0; i < balls.length; i++)
        {
            balls[i].update();
            
            if(balls[i].getX() < 0 || balls[i].getX() + balls[i].getD() > width)
            {
                balls[i].shiftX();
                balls[i].update();
            }

            if(balls[i].getY() < 0)
            {
                balls[i].shiftY();
                balls[i].update();
            }
            else if(balls[i].getY() + balls[i].getD() > height)
            {
                balls[i].shiftY();
                balls[i].updateVelocity();
                balls[i].setY(height - balls[i].getD());
            }
        }

    }

    /**
     *  
     * @uml.property name="ball"
     * @uml.associationEnd multiplicity="(0 -1)" ordering="ordered" aggregation="composite" elementType="gravity1.Ball"
     */
    private Ball[] balls;

    /**
     *  
     * @uml.property name="ball"
     */
    public Ball[] getBalls() {
        return balls;
    }

    /**
     *  
     * @uml.property name="ball"
     */
    public void setBalls(Ball[] balls) {
        this.balls = balls;
    }
}
