public class Matrix3x3 {
  
  private float m[][] = new float[3][3];
  
  
  public Matrix3x3() {
  }
  
  
  public Matrix3x3(float m[][]) {
    this.m[0][0] = m[0][0];
    this.m[0][1] = m[0][1];
    this.m[0][2] = m[0][2];
    this.m[1][0] = m[1][0];
    this.m[1][1] = m[1][1];
    this.m[1][2] = m[1][2];
    this.m[2][0] = m[2][0];
    this.m[2][1] = m[2][1];
    this.m[2][2] = m[2][2];
  }
  
  
  public Matrix3x3 product(Matrix3x3 m2) {
    float nm[][] = new float[3][3];
    
    for(int r = 0; r < 3; r++) {
      for(int c = 0; c < 3; c++) {
        nm[r][c] = (m[r][0] * m2.m[0][c]) + (m[r][1] * m2.m[1][c]) + (m[r][2] * m2.m[2][c]);
      }
    }
    
    return new Matrix3x3(nm);
  }
  
  
  public Vector2 product(Vector2 v) {
    int v0 = v.getX();
    int v1 = v.getY();
    int v2 = 1;

    return new Vector2(
      round(v0 * m[0][0] + v1 * m[0][1] + v2 * m[0][2]),
      round(v0 * m[1][0] + v1 * m[1][1] + v2 * m[1][2])
    );
  }
  
  
  public void setupTranslationMatrix(int dx, int dy) {
      m[0][0]=1; m[0][1]=0; m[0][2]=dx;
      m[1][0]=0; m[1][1]=1; m[1][2]=dy;
      m[2][0]=0; m[2][1]=0; m[2][2]=1;
  }
  
  
  public void setupRotationMatrix(float b) {
      m[0][0]=cos(b); m[0][1]=-1 * sin(b); m[0][2]=0;
      m[1][0]=sin(b); m[1][1]=cos(b)     ; m[1][2]=0;
      m[2][0]=0;      m[2][1]=0          ; m[2][2]=1;
  }
  
  
  public void setupScaleMatrix(float sx, float xy) {
      m[0][0]=sx; m[0][1]=0;  m[0][2]=0;
      m[1][0]=0;  m[1][1]=sy; m[1][2]=0;
      m[2][0]=0;  m[2][1]=0;  m[2][2]=1;
  }
  
  
  public void setupRotationMatrix(float b, int xr, int yr) {
      m[0][0]=cos(b); m[0][1]=-sin(b); m[0][2]=xr*(1-cos(b))+(yr*sin(b));
      m[1][0]=sin(b); m[1][1]=cos(b);  m[1][2]=yr*(1-cos(b))-(xr*sin(b));
      m[2][0]=0;      m[2][1]=0;       m[2][2]=1;
  }
  
  
  public void setupScaleMatrix(float sx, float sy, int x1, int y1) {
      m[0][0]=sx; m[0][1]=0;  m[0][2]=x1*(1-sx);
      m[1][0]=0;  m[1][1]=sy; m[1][2]=y1*(1-sy);
      m[2][0]=0;  m[2][1]=0;  m[2][2]=1;
  }
  
  
  public void setupIdentityMatrix() {
      m[0][0]=1; m[0][1]=0; m[0][2]=0;
      m[1][0]=0; m[1][1]=1; m[1][2]=0;
      m[2][0]=0; m[2][1]=0; m[2][2]=1;
  }
  
}

