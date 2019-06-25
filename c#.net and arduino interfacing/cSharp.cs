
    public partial class Form1 : Form
    { private SerialPort myport;
        public Form1()
        {
            InitializeComponent();
            Init();
        }
        private void button1_Click(object sender, EventArgs e)
        {
            myport.WriteLine("N");
        }
        private void Init()
        {
            myport = new SerialPort();
            myport.BaudRate = 9600;
            myport.PortName = "COM10";
            myport.Open();
        }
        private void button2_Click(object sender, EventArgs e)
        {
            myport.WriteLine("F");
        }
    }
}
