import fr.dgac.ivy.*;
 
class IvyHandler implements IvyMessageListener {
  private Ivy bus;
  
  IvyHandler(String name) throws IvyException {
    bus = new Ivy(name, name + " Ready",null);
    // classical subscription
    bus.bindMsg("^Hello(.*)",this);
    // inner class subscription ( think awt )
    bus.bindMsg("^Bye$",new IvyMessageListener() {
      public void receive(IvyClient client, String[] args) {
 // leaves the bus, and as it is the only thread, quits
        bus.stop();
      }
    });
    bus.start(null); // starts the bus on the default domain
  }

  // callback associated to the "Hello" messages"
  public void receive(IvyClient client, String[] args) {
    try {
      bus.sendMsg("Bonjour"+((args.length>0)?args[0]:""));
    } catch (IvyException ie) {
      System.out.println("can't send my message on the bus");
    }
  }
  
    public void send(String data) {
    try {
      bus.sendMsg(data);
    } catch (IvyException ie) {
      System.out.println("can't send my message on the bus");
    }
  }

  public static void main(String args[]) throws IvyException {
    new IvyHandler("A Handler");
  }
}
