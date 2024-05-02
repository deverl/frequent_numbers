import java.util.*;

public class FrequentNumbers {
    static List<Integer> getMostFrequentNumbers(int[] nums, int k)  {

        Map<Integer, Integer> m = new HashMap<Integer, Integer>();

        // Put count of all the distinct elements in Map with element as the key & count as the value.
        for (int i = 0; i < nums.length; i++) {
            // Get the count for the element if already present in the Map or get the default value which is 0.
            m.put(nums[i], m.getOrDefault(nums[i], 0) + 1);
        }

        // Create a list from elements of the map
        List<Map.Entry<Integer, Integer> > list = new ArrayList<Map.Entry<Integer, Integer> >(m.entrySet());

        // Sort the list
        Collections.sort(
            list,
            new Comparator<Map.Entry<Integer, Integer> >() {
                public int compare(Map.Entry<Integer, Integer> o1, Map.Entry<Integer, Integer> o2) {
                    return o2.getValue() - o1.getValue();
                }
        });
    
        List<Integer> l = new ArrayList<Integer>();

        for (int i = 0; i < k; i++) {
            l.add(list.get(i).getKey());
        }
        
        return l;
    }

    static void printArray(String prefix, int[] nums) {
        System.out.print(prefix + " [ ");
        for (int i = 0; i < nums.length; i++) {
            if (i > 0) {
                System.out.print(", ");
            }
            System.out.print(nums[i]);
        }
        System.out.println(" ]");
    }


    static void printList(String prefix, List<Integer> nums) {
        System.out.print(prefix + " [ ");
        int i = 0;
        for (int n : nums) {
            if (i > 0) {
                System.out.print(", ");
            }
            System.out.print(n);
            i++;
        }
        System.out.println(" ]");
    }


    static void runTest(int[] nums, int k) {
        List<Integer> l = getMostFrequentNumbers(nums, k);
        System.out.println("");
        printArray("  nums:", nums);
        System.out.println("     k: " + k);
        printList("result:", l);
    }

    public static void main(String[] args) {
        int nums1[] = {1,1,1,2,2,3};
        int k1 = 2;

        runTest(nums1, k1);

        int nums2[] = {1,4,2,5,7,5,4,4,5,5,5,2,7,2,5,4};
        int k2 = 3;

        runTest(nums2, k2);

        int nums3[] = { 9,3,9,3,9,3,7,9,7,2,9,4,4,9,4,4,4,9,9,8,8,6,6,1,1,1,1,1,1 };
        int k3 = 4;

        runTest(nums3, k3);

        System.out.println("");
    }
}
