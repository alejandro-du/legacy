/*
 * Created on 20/07/2005
 *
 * TODO To change the template for this generated file go to
 * Window - Preferences - Java - Code Style - Code Templates
 */
package gravity1;

import javax.swing.JApplet;

/**
 * @author Alejandro Duarte
 * 
 * TODO To change the template for this generated type comment go to
 * Window - Preferences - Java - Code Style - Code Templates
 */

public class App extends JApplet implements Runnable
{
    public void start()
    {
        setSimulation(new Simulation(getWidth(), getHeight()));
        
        setScene(new Scene(createImage(getWidth(), getHeight()), simulation.getBalls()));
        
        add(getScene());
        
        Thread th = new Thread(this); // create the animation thread
        th.start();
    }
    
    /* (non-Javadoc)
     * @see java.lang.Runnable#run()
     */
    public void run()
    {
        // TODO Auto-generated method stub
        for(;;)
        {
            simulation.update();
            scene.update();
            
            try
            {
                Thread.sleep(20);
            }
            catch(Exception e)
            {
            }
        }
    }

    /**
     *  
     * @uml.property name="scene"
     * @uml.associationEnd multiplicity="(1 1)" aggregation="composite"
     */
    private Scene scene;

    /**
     *  
     * @uml.property name="scene"
     */
    public Scene getScene() {
        return scene;
    }

    /**
     *  
     * @uml.property name="scene"
     */
    public void setScene(Scene scene) {
        this.scene = scene;
    }

    /**
     *  
     * @uml.property name="simulation"
     * @uml.associationEnd multiplicity="(1 1)" aggregation="composite"
     */
    private Simulation simulation;

    /**
     *  
     * @uml.property name="simulation"
     */
    public Simulation getSimulation() {
        return simulation;
    }

    /**
     *  
     * @uml.property name="simulation"
     */
    public void setSimulation(Simulation simulation) {
        this.simulation = simulation;
    }

}
