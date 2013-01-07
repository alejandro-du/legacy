/*
 * Created on 20/07/2005
 *
 * TODO To change the template for this generated file go to
 * Window - Preferences - Java - Code Style - Code Templates
 */
package gravity1;


//import java.awt.Color;
import java.awt.Graphics;
import java.awt.Image;
import javax.swing.JPanel;


/**
 * @author Compaq
 * 
 * TODO To change the template for this generated type comment go to
 * Window - Preferences - Java - Code Style - Code Templates
 */

public class Scene extends JPanel
{
    private Image backBuffer;
    
    public Scene(Image backBuffer, Ball balls[])
    {
        this.backBuffer = backBuffer;
        this.balls = balls;
        setSize(backBuffer.getWidth(this), backBuffer.getHeight(this));
    }
    
    
    public void update()
    {
        repaint();
    }

    
    public void paint(Graphics g)
    {
        Graphics gbb = backBuffer.getGraphics();
        
        gbb.clearRect(0, 0, backBuffer.getWidth(this),  backBuffer.getHeight(this));
        
        for(int i = 0; i < balls.length; i++)
        {
            gbb.fillOval(balls[i].getX(), balls[i].getY(), balls[i].getD(), balls[i].getD());
        }
        
        g.drawImage(backBuffer, 0, 0, this); // draw the animation frame onto this
    }

    /**
     *  
     * @uml.property name="ball"
     * @uml.associationEnd multiplicity="(0 -1)" ordering="ordered" aggregation="aggregate" elementType="gravity1.Ball"
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
