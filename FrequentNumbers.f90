!------------------------------------------------------------------------------
! most_frequent.f90
!
! A Fortran translation of the original C++ program that finds the k most
! frequently occurring values in an array of integers.
!
! Build : gfortran -O2 -o most_frequent most_frequent.f90
! Run   : ./most_frequent                 (uses the canned test data)
!         ./most_frequent 1000 50 5        (random data: count, max, k)
!
! Set the environment variable NO_TRUNCATE_ARRAYS=1 to print arrays in full.
!------------------------------------------------------------------------------

module freq_mod
    implicit none
    private
    public :: get_most_frequent_numbers, print_vec, run_test, &
              run_random_inputs_test, int_from_string
contains

    !--------------------------------------------------------------------------
    ! Read an environment variable and interpret it as an integer, falling
    ! back to default_value if it is unset or does not parse.
    !--------------------------------------------------------------------------
    integer function get_env_var_as_int(name, default_value) result(res)
        character(len=*), intent(in) :: name
        integer,          intent(in) :: default_value
        character(len=256) :: val
        integer :: status, ios, tmp

        call get_environment_variable(name, val, status=status)
        if (status == 0 .and. len_trim(val) > 0) then
            read(val, *, iostat=ios) tmp
            if (ios == 0) then
                res = tmp
            else
                res = default_value
            end if
        else
            res = default_value
        end if
    end function get_env_var_as_int

    !--------------------------------------------------------------------------
    ! Tally how many times each distinct value occurs in nums. The unique
    ! values are returned in their order of first appearance.
    !--------------------------------------------------------------------------
    subroutine count_frequencies(nums, vals, counts)
        integer,              intent(in)  :: nums(:)
        integer, allocatable, intent(out) :: vals(:), counts(:)
        integer, allocatable :: tv(:), tc(:)
        integer :: i, j, nunique
        logical :: found

        allocate(tv(size(nums)), tc(size(nums)))
        nunique = 0
        do i = 1, size(nums)
            found = .false.
            do j = 1, nunique
                if (tv(j) == nums(i)) then
                    tc(j) = tc(j) + 1
                    found = .true.
                    exit
                end if
            end do
            if (.not. found) then
                nunique = nunique + 1
                tv(nunique) = nums(i)
                tc(nunique) = 1
            end if
        end do

        allocate(vals(nunique), counts(nunique))
        vals   = tv(1:nunique)
        counts = tc(1:nunique)
    end subroutine count_frequencies

    !--------------------------------------------------------------------------
    ! Stable insertion sort of (vals, counts) by vals ascending. This mirrors
    ! the ascending key ordering of the std::map in the original, so that ties
    ! in frequency break deterministically by value.
    !--------------------------------------------------------------------------
    subroutine sort_by_value_asc(vals, counts)
        integer, intent(inout) :: vals(:), counts(:)
        integer :: i, j, kv, kc

        do i = 2, size(vals)
            kv = vals(i); kc = counts(i)
            j = i - 1
            do while (j >= 1)
                if (vals(j) > kv) then
                    vals(j+1)   = vals(j)
                    counts(j+1) = counts(j)
                    j = j - 1
                else
                    exit
                end if
            end do
            vals(j+1)   = kv
            counts(j+1) = kc
        end do
    end subroutine sort_by_value_asc

    !--------------------------------------------------------------------------
    ! Stable insertion sort of (vals, counts) by counts descending. Stability
    ! preserves the ascending-by-value order established above for equal counts.
    !--------------------------------------------------------------------------
    subroutine sort_by_count_desc(vals, counts)
        integer, intent(inout) :: vals(:), counts(:)
        integer :: i, j, kv, kc

        do i = 2, size(counts)
            kv = vals(i); kc = counts(i)
            j = i - 1
            do while (j >= 1)
                if (counts(j) < kc) then
                    vals(j+1)   = vals(j)
                    counts(j+1) = counts(j)
                    j = j - 1
                else
                    exit
                end if
            end do
            vals(j+1)   = kv
            counts(j+1) = kc
        end do
    end subroutine sort_by_count_desc

    !--------------------------------------------------------------------------
    ! Return the k values that occur most often in nums, most frequent first.
    !--------------------------------------------------------------------------
    function get_most_frequent_numbers(nums, k) result(r)
        integer, intent(in) :: nums(:)
        integer, intent(in) :: k
        integer, allocatable :: r(:)
        integer, allocatable :: vals(:), counts(:)
        integer :: i

        call count_frequencies(nums, vals, counts)
        call sort_by_value_asc(vals, counts)
        call sort_by_count_desc(vals, counts)

        allocate(r(k))
        do i = 1, k
            r(i) = vals(i)
        end do
    end function get_most_frequent_numbers

    !--------------------------------------------------------------------------
    ! Print "label[ a, b, c ]", truncating after 30 elements unless the
    ! NO_TRUNCATE_ARRAYS environment variable is set to a non-zero value.
    !--------------------------------------------------------------------------
    subroutine print_vec(s, v)
        character(len=*), intent(in) :: s
        integer,          intent(in) :: v(:)
        integer :: no_truncate_arrays, i
        character(len=32) :: numstr

        no_truncate_arrays = get_env_var_as_int("NO_TRUNCATE_ARRAYS", 0)

        write(*, '(A)', advance='no') s // "[ "
        do i = 1, size(v)
            if (i > 1) write(*, '(A)', advance='no') ", "
            if (no_truncate_arrays == 0 .and. (i - 1) >= 30) then
                write(*, '(A)', advance='no') "... "
                exit
            end if
            write(numstr, '(I0)') v(i)
            write(*, '(A)', advance='no') trim(numstr)
        end do
        write(*, '(A)') " ]"
    end subroutine print_vec

    !--------------------------------------------------------------------------
    ! Run one test case and print the inputs alongside the result.
    !--------------------------------------------------------------------------
    subroutine run_test(nums, k)
        integer, intent(in) :: nums(:)
        integer, intent(in) :: k
        integer, allocatable :: v(:)

        v = get_most_frequent_numbers(nums, k)

        write(*, '(A)') ''
        write(*, '(A, I0)') "     n: ", size(nums)
        call print_vec("  nums: ", nums)
        write(*, '(A, I0)') "     k: ", k
        call print_vec("result: ", v)
    end subroutine run_test

    !--------------------------------------------------------------------------
    ! Seed the intrinsic random number generator from the system clock.
    !--------------------------------------------------------------------------
    subroutine seed_random()
        integer :: n, i, clock
        integer, allocatable :: seed(:)

        call random_seed(size=n)
        allocate(seed(n))
        call system_clock(count=clock)
        do i = 1, n
            seed(i) = clock + 37 * i
        end do
        call random_seed(put=seed)
    end subroutine seed_random

    !--------------------------------------------------------------------------
    ! Build a vector of num_data_points random integers in [0, max_value)
    ! and run the most-frequent test on it.
    !--------------------------------------------------------------------------
    subroutine run_random_inputs_test(num_data_points, max_value, num_most_frequent)
        integer, intent(in) :: num_data_points, max_value, num_most_frequent
        integer, allocatable :: nums(:)
        integer :: i
        real :: x

        call seed_random()
        allocate(nums(num_data_points))
        do i = 1, num_data_points
            call random_number(x)
            nums(i) = int(x * max_value)
        end do

        call run_test(nums, num_most_frequent)
    end subroutine run_random_inputs_test

    !--------------------------------------------------------------------------
    ! Parse an integer from a string, ignoring every non-digit character.
    !--------------------------------------------------------------------------
    integer function int_from_string(str) result(res)
        character(len=*), intent(in) :: str
        character(len=len(str)) :: sanitized
        integer :: i, n, ios

        n = 0
        sanitized = ''
        do i = 1, len_trim(str)
            if (str(i:i) >= '0' .and. str(i:i) <= '9') then
                n = n + 1
                sanitized(n:n) = str(i:i)
            end if
        end do

        if (n == 0) then
            res = 0
        else
            read(sanitized(1:n), *, iostat=ios) res
            if (ios /= 0) res = 0
        end if
    end function int_from_string

end module freq_mod


program most_frequent
    use freq_mod
    implicit none

    character(len=256) :: arg1, arg2, arg3
    integer :: num_data_points, max_value, num_most_frequent

    ! command_argument_count() excludes the program name, so the original
    ! C++ test of argc > 3 (i.e. three user-supplied arguments) becomes >= 3.
    if (command_argument_count() >= 3) then
        ! Run with user-supplied inputs: number of data points, the maximum
        ! integer value of a data point, and the number of results to return.
        call get_command_argument(1, arg1)
        call get_command_argument(2, arg2)
        call get_command_argument(3, arg3)

        num_data_points   = int_from_string(trim(arg1))
        max_value         = int_from_string(trim(arg2))
        num_most_frequent = int_from_string(trim(arg3))

        call run_random_inputs_test(num_data_points, max_value, num_most_frequent)
    else
        ! Run with some canned data.
        call run_test([1, 1, 1, 2, 2, 3], 2)

        call run_test([1, 4, 2, 5, 7, 5, 4, 4, 5, 5, 5, 2, 7, 2, 5, 4], 3)

        call run_test([9, 3, 9, 3, 9, 3, 7, 9, 7, 2, 9, 4, 4, 9, 4, 4, 4, 9, &
                       9, 8, 8, 6, 6, 1, 1, 1, 1, 1, 1], 4)
    end if

    write(*, '(A)') ''
end program most_frequent
