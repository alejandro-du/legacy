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

public class Ball
{

    /**
     * 
     * @uml.property name="x" 
     */
    private int d;
    private int x;

    /**
     * 
     * @uml.property name="y" 
     */
    private int y;

    private int vy;
    private int vx;
    private int ay;
    
    public Ball(int x, int y, int d, int vx)
    {
        this.x = x;
        this.y = y;
        this.d = d;
        this.vx = vx;
        vy = 0;
        ay = 1;
    }
    
    public int getD()
    {
        return d;
    }

    /**
     * 
     * @uml.property name="x"
     */
    public int getX()
    {
        return x;
    }

    public int getY()
    {
        return y;
    }

    /**
     * 
     * @uml.property name="y"
     */
    public void setY(int y)
    {
        this.y = y;
    }

    public void update()
    {
        updateVelocity();
        updatePosition();
    }
    
    public void updatePosition()
    {
        x += vx;
        y += vy;
    }

    public void updateVelocity()
    {
        vy += ay;
    }

    public void shiftX()
    {
        vx = -vx;
    }

    public void shiftY()
    {
        vy = -vy;
    }
}    
