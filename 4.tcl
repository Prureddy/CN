# Simulator Instance Creation
set ns [new Simulator]
# Fixing the coordinate of simulation area
set val(x) 500
set val(y) 500
# Define options
set val(chan) Channel/WirelessChannel ;# channel type
set val(prop) Propagation/TwoRayGround ;# radio-propagation model
set val(netif) Phy/WirelessPhy ;# network interface type
set val(mac) Mac/802_11 ;# MAC type
set val(ifq) Queue/DropTail/PriQueue ;# interface queue type
set val(ll) LL ;# link layer type
set val(ant) Antenna/OmniAntenna ;# antenna model
set val(ifqlen) 50 ;# max packet in ifq
set val(nn) 2 ;# number of mobilenodes
set val(rp) AODV ;# routing protocol
set val(stop) 10.0 ;# time of simulation end
set val(z) 0 ;# Z dimension of topography
# set up topography object
set topo [new Topography]
$topo load_flatgrid $val(x) $val(y)
# Nam File Creation - network animator
set namfile [open sample1.nam w]
# Tracing all the events and configuration
$ns namtrace-all-wireless $namfile $val(x) $val(y)
# Trace File creation
set tracefile [open sample1.tr w]
# Tracing all the events and configuration
$ns trace-all $tracefile 
# general operational descriptor- storing the hop details in the network create-god $val(nn)
create-god $val(nn)
# configure the nodes
$ns node-config -adhocRouting $val(rp) \
-llType $val(ll) \
-macType $val(mac) \
-ifqType $val(ifq) \
-ifqLen $val(ifqlen) \
-antType $val(ant) \
-propType $val(prop) \
-phyType $val(netif) \
-channelType $val(chan) \
-topoInstance $topo \
-agentTrace ON \
-routerTrace ON \
-macTrace OFF \
-movementTrace ON
# Node Creation
set node1 [$ns node]
set node2 [$ns node]
# Initial color of the nodes
$node1 color black
$node2 color black
# Location fixing for the nodes
$node1 set X_ 200
$node1 set Y_ 100
$node1 set Z_ $val(z)
$node2 set X_ 200
$node2 set Y_ 300
$node2 set Z_ $val(z)
# Label and coloring
$ns at 0.1 "$node1 color blue"
$ns at 0.1 "$node1 label Node1"
$ns at 0.1 "$node2 label Node2"
# Size of the node
$ns initial_node_pos $node1 30
$ns initial_node_pos $node2 30
# Ending nam and the simulation
$ns at $val(stop) "$ns nam-end-wireless $val(stop)"
$ns at $val(stop) "stop"
# Stopping the scheduler
proc stop {} {
 global namfile tracefile ns
 $ns flush-trace
 close $namfile
 close $tracefile 
 # Executing nam file
 exec nam sample1.nam &
}
# Starting scheduler
$ns run
