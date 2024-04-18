import java.util.*;

public class FrequentNumbers {
	static List<Integer> getMostFrequentNumbers(int[] nums, int k)	{

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

	public static void main(String[] args) {
		int nums[] = { 9,3,9,3,9,3,7,9,7,2,9,4,4,9,4,4,4,9,9,8,8,6,6,1,1,1,1,1,1 };
		int k = 4;
		int i = 0;
		
		List<Integer> l = getMostFrequentNumbers(nums, k);
		
		String s = "The " + k + " numbers with the highest frequency are:";
		
		for (int n : l) {
			if (i > 0) {
				s += ",";
			}
			s += " " + n;
			i++;
		}

		System.out.println(s);
	}
}
