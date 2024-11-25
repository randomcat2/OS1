import java.util.*;

class Process {
    int id;
    int arrival;
    int burst;
    int completion;
    int remaining;
    int waiting;
    int turnaround;
    int response;
    boolean inReadyQueue;
    boolean completed;

    Process(int id, int arrival, int burst) {
        this.id = id;
        this.arrival = arrival;
        this.burst = burst;
        this.remaining = burst;
        this.waiting = 0;
        this.turnaround = 0;
        this.response = -1;
        this.inReadyQueue = false;
        this.completed = false;
    }
}

public class Main {
    public static void roundRobin(List<Process> processes) {
        Queue<Process> readyQueue = new LinkedList<>();
        Scanner sc = new Scanner(System.in);

        System.out.print("Enter time quantum: ");
        int timeQuantum = sc.nextInt();

        int currentTime = 0;
        int completedProcesses = 0;

        // Add initial processes to the ready queue
        for (Process process : processes) {
            if (!process.completed && currentTime >= process.arrival && !process.inReadyQueue) {
                readyQueue.add(process);
                process.inReadyQueue = true;
            }
        }

        while (completedProcesses < processes.size()) {
            Process currentProcess = readyQueue.poll();

            if (currentProcess.response == -1) {
                currentProcess.response = currentTime - currentProcess.arrival;
            }

            int timeSlice = Math.min(currentProcess.remaining, timeQuantum);
            currentTime += timeSlice;
            currentProcess.remaining -= timeSlice;

            // Add new arrivals to the ready queue
            for (Process process : processes) {
                if (!process.completed && currentTime >= process.arrival && !process.inReadyQueue) {
                    readyQueue.add(process);
                    process.inReadyQueue = true;
                }
            }

            if (currentProcess.remaining > 0) {
                readyQueue.add(currentProcess);
            } else {
                completedProcesses++;
                currentProcess.completion = currentTime;
                currentProcess.turnaround = currentProcess.completion - currentProcess.arrival;
                currentProcess.waiting = currentProcess.turnaround - currentProcess.burst;
                currentProcess.completed = true;
            }
        }

        // Print results
        System.out.println("Id\tAT\tBT\tCT\tTAT\tWT\tRT");
        for (Process process : processes) {
            System.out.println(process.id + "\t" + process.arrival + "\t" + process.burst + "\t" +
                    process.completion + "\t" + process.turnaround + "\t" +
                    process.waiting + "\t" + process.response);
        }
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        System.out.print("Number of processes: ");
        int n = sc.nextInt();

        List<Process> processes = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            System.out.print("Enter arrival and burst time for process " + i + ": ");
            int arrival = sc.nextInt();
            int burst = sc.nextInt();
            processes.add(new Process(i, arrival, burst));
        }

        roundRobin(processes);
    }
}
